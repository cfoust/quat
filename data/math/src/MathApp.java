import java.util.ArrayList;

/**
 * Created by caleb on 3/1/16.
 */
public class MathApp {
    public static void main(String[] args) throws Exception {
        // Load up the wordmap from a file (compiles it into a .map if necessary)
        WordMap old = WordMap.fromFile("../words");

        // Heuristic class that has functions that determine a word and a puzzle's difficulty
        // 4000 is the frequency above which we assume the average user knows all the words
        ThreshHeuristic h = new ThreshHeuristic(4000);

        /*
        Generates the puzzles. 3000 is the frequency above which all start and end words should be. 300 is the easiness
        that all start and end words should be above. (An easiness value of 300 means that for every start and end word,
        the average user is guaranteed to be able to think up the equivalent of 3 words.)
         */
        PuzzleGenerator gen = new PuzzleGenerator(old, h, 1000, 40);

        GaussianFunction func = new GaussianFunction(0, 2.23);

        int TOTAL_PROBLEMS = 12000,
            buckets = 250;

        int[] bucketCounts = new int[buckets];
        double[] bucketDiff = new double[buckets];

        double step = ((float) TOTAL_PROBLEMS / (float) buckets) / (float) TOTAL_PROBLEMS,
               dist = step * 12;

        int total = 0, // Total number of puzzles needed to cover curve
            diffMax = 688, // Max difficulty
            diffMin = 44, // Min difficulty
            diffDiff = diffMax - diffMin; // The difference between them

        double diffStep = (double) diffDiff / (double) buckets;

        // Initialize our array of buckets
        ArrayList<ArrayList<Puzzle>> puzzleBuckets = new ArrayList<>(buckets);
        for (int i = 0; i < buckets; i++) {
            puzzleBuckets.add(new ArrayList<Puzzle>());
        }

        // Calculates how many puzzles should be in each bucket
        for (int i = 0; i < buckets; i++) {
            double calc = func.eval(dist*i - 6.0f) / 0.18,
                   difficulty = (diffStep * i) + diffMin;
            int result = (int) Math.floor(calc * TOTAL_PROBLEMS * 0.009);
//            int result = (int) Math.floor(calc * TOTAL_PROBLEMS * 0.001);

            total += result;

            bucketCounts[i] = result;
            bucketDiff[i] = difficulty;

//            System.out.printf("Bucket #%d %f %d %f\n", i+1, calc, result, difficulty);
        }
        System.out.println(total);

        int cutoffThreshold = (int) Math.floor((double) total * 0.13);

        // Now generate the puzzles
        int puzzlesGenerated = 0;
        while (true) {
            // Generate a new puzzle
            ArrayList<String> sol = gen.generatePuzzle();
            puzzlesGenerated++;

            if ((puzzlesGenerated % 1000) == 0) {
                System.out.println("Diagnostic Scan of Generation:");
                System.out.printf("Puzzles generated: %d\n", puzzlesGenerated);
                int needed = 0;
                for (int i = 0; i < buckets; i++) {
                    if (bucketCounts[i] > puzzleBuckets.get(i).size()) {
                        int difference = bucketCounts[i] - puzzleBuckets.get(i).size();
                        needed += difference;
                    }
                }
                System.out.printf("Need %d more puzzles filled. (%d to cut off)\n", needed, cutoffThreshold);
                if (needed < cutoffThreshold) {
                    break;
                }
            }

            // Make sure it's not null
            if (sol == null) {
                break;
//                continue;
            }

            int easiness = h.puzzleEasiness(old, sol);

            // Scan to see where we should put this puzzle
            for (int i = 0; i < buckets; i++) {
                ArrayList<Puzzle> bucket = puzzleBuckets.get(i);
                Puzzle thisPuzzle = new Puzzle(sol, easiness);

                if ((Math.abs(bucketDiff[i] - (double) easiness) < 3) &&
                    (bucketCounts[i] > bucket.size())){
                    boolean exists = false;
                    for (Puzzle puzzle : bucket) {
                        if (thisPuzzle.equals(puzzle)) {
                            exists = true;
                        }
                    }
                    if (!exists) {
                        puzzleBuckets.get(i).add(thisPuzzle);
                    }
                    break;
                }
            }

            // Scan to see if all buckets are full
            boolean cutOff = true;
            for (int i = 0; i < buckets; i++) {
                if (bucketCounts[i] > puzzleBuckets.get(i).size()){
                    cutOff = false;
                }
            }

            if (cutOff) {
                break;
            }
        }



        // Dump them to a file
        ArrayList<Puzzle> puzzles = new ArrayList<>();
        for (ArrayList<Puzzle> bucket : puzzleBuckets) {
            for (Puzzle puzzle : bucket) {
                puzzles.add(puzzle);
            }
        }
        System.out.printf("%d puzzles generated to make %d total. Actually ended with %d.\n", puzzlesGenerated, total, puzzles.size());

        JSGenerator.dumpToFile(old, puzzles, "../words2.js");


    }
}
