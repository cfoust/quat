import com.google.common.hash.HashFunction;
import com.google.common.hash.Hashing;

import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.lang.reflect.Array;
import java.util.*;

/**
 * Created by caleb on 3/1/16.
 */
public class MathApp {
    public static void main(String[] args) throws Exception {
        if (args.length == 0) {
            return;
        }

        // Load up the wordmap from a file (compiles it into a .map if necessary)
        WordMap map = WordMap.fromFile("../words");

        // The heuristic we use for judging the difficulty of a puzzle
        HeuristicSet h = new ThreshHeuristic(5000);

        // Grabs the first arg, we know we have at least one
        String arg = args[0];

        /* Builds a solution file (.quat) that has the solution for EVERY SINGLE PUZZLE IMAGINABLE. */
        if (arg.equals("buildsols")) {
            // Grabs the second argument for the out name. Maybe do some value checking here.
            String outName = args[1];

            // FileOutputStream we use for writing out the binary out file.
            FileOutputStream fos = new FileOutputStream(outName);

            // The map of all words in the English language and their successors
            Set<Map.Entry<String, Word>> wordEntries = map.words.entrySet();

            // Make that map into an array
            ArrayList<Word> words = new ArrayList<>();
            for (Map.Entry<String, Word> entry : wordEntries) {
                words.add(entry.getValue());
            }


            int puzzleCount = 0, // Records the total number of puzzles
                size = 220000000; // Upper bound for the hash array.

            /* Hash array. Just a boolean because all we need to know is whether the puzzle
            * has been generated yet, since we write all successful ones to file.*/
            boolean[] hashes = new boolean[size];

            // Initialize the array to false (just as a precaution)
            for (int i = 0; i < hashes.length; i++) {
                hashes[i] = false;
            }

            // The hash function we use to reduce collisions (still results in a million or so)
            HashFunction f = Hashing.murmur3_32();

            // Holds the bytes for a bunch of puzzles before they're written to file.
            ArrayList<byte[]> puzzleBytes = new ArrayList<>();

            // Records the start so we can keep track of how long it's taking us to do this.
            long start = System.currentTimeMillis(), time = start;

            // The count is how many we've tried, exists is how many existed, noSol is how many had no solution
            int count = 0, exists = 0, noSol = 0;

            // Iterate through all the possible word pairings (32 million)
            for (int i = 0; i < words.size(); i++) {
                String word = words.get(i).getWord();
                for (int j = 0; j < words.size(); j++) {
                    count++;

                    // Ignore going from the current word to the same word
                    if (i == j) continue;

                    // Gets the other word's string
                    String other = words.get(j).getWord();

                    /* We have to calculate two hashes because a puzzle is considered to equivalent to another
                    * if the word PAIRING is the same, i.e the order of the two words is not important.*/

                    // Genereate first hash
                    int hash1 = f.hashBytes((word + other).getBytes()).asInt() % hashes.length;
                    if (hash1 < 0)
                    {
                        hash1 += hashes.length;
                    }

                    // Generate second hash
                    int hash2 = f.hashBytes((other + word).getBytes()).asInt() % hashes.length;
                    if (hash2 < 0)
                    {
                        hash2 += hashes.length;
                    }

                    // Check to see if either of them have already been generated
                    if ((hashes[hash1]) || (hashes[hash2])) {
                        exists++;
                        continue;
                    }

                    // We prefer to use the first hash, set that to true
                    hashes[hash1] = true;

                    // Generate the optimal solution
                    ArrayList<String> sol = map.solve(word, other);

                    // If it doesn't exist, continue
                    if (sol == null) {
                        noSol++;
                        continue;
                    }

                    // Create a Puzzle object for the solution and convert it to our special byte code
                    Puzzle p = new Puzzle(sol);
                    puzzleBytes.add(p.toBytes());

                    puzzleCount++;

                    // Flush to file every 50,000 puzzles
                    if ((puzzleCount % 50000) == 0) {
                        // This all calculates how long the previous 50,000 took
                        long sinceStart = System.currentTimeMillis() - start;
                        double secSinceStart = ((double) sinceStart) / 1000.0f;
                        long current = System.currentTimeMillis() - time;
                        double sec = ((double) current) / 1000.0f;

                        // Print out some diagnostic data
                        System.out.printf("COUNT: %d PUZZLES: %d COLLISIONS: %d NOSOLS: %d 50k: %.2f sec. TOTAL: %.2f\n", count,puzzleCount, exists, noSol,  sec, secSinceStart);

                        // Flush to file
                        for (byte[] arr : puzzleBytes) {
                            fos.write(arr);
                        }
                        fos.flush();

                        // Clear the puzzle byte array
                        puzzleBytes.clear();

                        // Record the system time again
                        time = System.currentTimeMillis();
                    }
                }
            }

            // Flush any remaining puzzles to file
            for (byte[] arr : puzzleBytes) {
                fos.write(arr);
            }
            fos.flush();

            // Print diagnostics and finish
            long sinceStart = System.currentTimeMillis() - start;
            double secSinceStart = ((double) sinceStart) / 1000.0f;
            System.out.printf("COUNT: %d PUZZLES: %d COLLISIONS: %d NOSOLS: %d TOTAL: %.2f\n", count, puzzleCount, exists, noSol, secSinceStart);
            System.out.printf("Wrote %d puzzles to %s.\n", puzzleCount, outName);

            fos.close();
        /* Does absolutely nothing other than parse a .quat file and measure how long it takes to
        * go through it. Usually it takes just a few seconds to parse a million puzzles.
        *
        * .quat files have <15 million puzzles (because 5500 choose 2 is 15 millionish).*/
        } else if (arg.equals("parsesols")) {
            // Grabs the second argument as the filename
            String filename = args[1];

            // PuzzleIterator is a special, memory-conserving class for reading the puzzles
            PuzzleIterator p = new PuzzleIterator(filename);

            // The number of puzzles parsed
            int puzzles = 0;

            // Records the time
            long time = System.currentTimeMillis();

            // Iterate through all the puzzles
            while (p.hasNext()) {
                Puzzle puzzle = p.next();
                puzzles++;

                // Calculate the difficulty (we don't use the value, but it's to measure how long it takes)
                int hardness = h.puzzleEasiness(map, puzzle.getSteps());

                // Record how long it took to parse a million puzzles and print it
                if ((puzzles % 1000000) == 0) {
                    long current = System.currentTimeMillis() - time;
                    System.out.printf("Million puzzles in %dms.\n", current);
                    time = System.currentTimeMillis();
                }
            }
            // Print the total number parsed
            System.out.println(puzzles);
        } else if (arg.equals("genpuzzles")) {
            // Grabs the second argument as the filename
            String filename = args[1];

            // PuzzleIterator is a special, memory-conserving class for reading the puzzles
            PuzzleIterator p = new PuzzleIterator(filename);

            // This is our function we generate the bell curve with.
            // This is so the game concentrates around a certain difficulty.
            GaussianFunction func = new GaussianFunction(0, 2.23);

            int TOTAL_PROBLEMS = 12000,
                    buckets = 250;

            // Holds the count for the number of puzzles in each bucket
            int[] bucketCounts = new int[buckets];

            // Holds the difficulty range for each bucket
            double[] bucketDiff = new double[buckets];

            // Calculates some random-ass percentage
            double step = ((float) TOTAL_PROBLEMS / (float) buckets) / (float) TOTAL_PROBLEMS,
                    dist = step * 12;

            int total = 0,
                diffMax = 688, // Max difficulty
                diffMin = 300, // Min difficulty
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
                int result = (int) Math.floor(calc * TOTAL_PROBLEMS * 0.020);

                total += result;

                bucketCounts[i] = result;
                bucketDiff[i] = difficulty;
            }

            int puzzlesGenerated = 0;
            String last = null;
            Random r = new Random();
            final int FREQUENCY_THRESHOLD = 300;
            String[] banned = {
                    "fuck",
                    "shit",
                    "kill",
                    "gook",
                    "damn",
                    "cunt",
                    "dick",
                    "rape",
                    "porn",
                    "cock"
            };
            while (p.hasNext()) {
                Puzzle puzz = p.next();

                // Skips pairings randomly if the start word is the same
                if (puzz.getFirst().equals(last) && (r.nextInt(10) > 4)) {
                    continue;
                }

                // Enforce some frequency rules
                int firstFrequency = map.get(puzz.getFirst()).getFrequency(),
                    lastFrequency = map.get(puzz.getLast()).getFrequency();
                if ((firstFrequency < FREQUENCY_THRESHOLD) || (lastFrequency < FREQUENCY_THRESHOLD)) {
                    continue;
                }

                boolean isBanned = false;
                for (String word : banned) {
                    if (puzz.getFirst().equals(word) || puzz.getLast().equals(word)) {
                        isBanned = true;
                        break;
                    }
                }
                if (isBanned) {
                    continue;
                }


                ArrayList<String> sol = puzz.getSteps();

                int easiness = h.puzzleEasiness(map, sol);

                // Scan to see where we should put this puzzle
                for (int i = 0; i < buckets; i++) {
                    ArrayList<Puzzle> bucket = puzzleBuckets.get(i);

                    if ((Math.abs(bucketDiff[i] - (double) easiness) < 3) &&
                            (bucketCounts[i] > bucket.size())){

                        boolean exists = false;
                        for (Puzzle puzzle : bucket) {
                            if (puzz.equals(puzzle)) {
                                exists = true;
                            }
                        }

                        if (exists) continue;

                        /*
                        Get the first word of this puzzle so we can cut down on similar pairs.
                         */
                        last = puzz.getFirst();

                        // Randomly swap the words in the puzzle with a half chance
                        if (r.nextInt(10) > 4) {
                            puzz.reverse();
                        }

                        // Add the puzzle to a bucket
                        puzzleBuckets.get(i).add(puzz);

                        puzzlesGenerated++;
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
            System.out.printf("%d puzzles generated.\n", puzzlesGenerated);

            // Dump them to a file
            ArrayList<Puzzle> puzzles = new ArrayList<>();
            for (ArrayList<Puzzle> bucket : puzzleBuckets) {
                for (Puzzle puzzle : bucket) {
                    puzzles.add(puzzle);
                }
            }
            JSGenerator.dumpToFile(map, puzzles, "../words2.js");
        }
    }
}
