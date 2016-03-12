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
        HeuristicSet h = new ThreshHeuristic(5000);

        String arg = args[0];

        if (arg.equals("buildsols")) {
            String outName = args[1];

            FileOutputStream fos = new FileOutputStream(outName);

            Set<Map.Entry<String, Word>> wordEntries = map.words.entrySet();

            ArrayList<Word> words = new ArrayList<>();
            for (Map.Entry<String, Word> entry : wordEntries) {
                words.add(entry.getValue());
            }

            int puzzleCount = 0, size = 220000000;
            boolean[] hashes = new boolean[size];
            for (int i = 0; i < hashes.length; i++) {
                hashes[i] = false;
            }




//            if (args.length == 3) {
//                String cacheName = args[2];
//                PuzzleIterator p = new PuzzleIterator(cacheName);
//
//                int cached = 0, collisions = 0;
//                Puzzle puzzle;
//                while (p.hasNext()) {
//                    puzzle = p.next();
//
//                    int hash = puzzle.hashCode() % hashes.length;
//                    if (hash < 0)
//                    {
//                        hash += hashes.length;
//                    }
//
//                    if (hashes[hash]) {
//                        collisions++;
//                        Puzzle o = hashPuzzles[hash];
//                        System.out.printf("%s collided with %s\n", puzzle.toString(), o.toString());
//                        if (collisions == 1000) {
//                            break;
//                        }
//                        continue;
//
//                    }
//
//                    hashes[hash] = true;
//                    hashPuzzles[hash] = puzzle;
//                    cached++;
//                }
//                System.out.printf("%d puzzles pulled from cache. (%d collisions) \n", cached, collisions);
//            }
            HashFunction f = Hashing.murmur3_32();

            ArrayList<byte[]> puzzleBytes = new ArrayList<>();
            long start = System.currentTimeMillis(), time = start;
            int count = 0, exists = 0, noSol = 0;
            for (int i = 0; i < words.size(); i++) {
                String word = words.get(i).getWord();
                for (int j = 0; j < words.size(); j++) {
                    count++;
                    if (i == j) continue;

                    String other = words.get(j).getWord();

                    int hash1 = f.hashBytes((word + other).getBytes()).asInt() % hashes.length;
                    if (hash1 < 0)
                    {
                        hash1 += hashes.length;
                    }

                    int hash2 = f.hashBytes((other + word).getBytes()).asInt() % hashes.length;
                    if (hash2 < 0)
                    {
                        hash2 += hashes.length;
                    }

                    if ((hashes[hash1]) || (hashes[hash2])) {
                        exists++;
                        continue;
                    }

                    hashes[hash1] = true;

                    ArrayList<String> sol = map.solve(word, other);

                    if (sol == null) {
                        noSol++;
                        continue;
                    }

                    Puzzle p = new Puzzle(sol);
                    puzzleBytes.add(p.toBytes());


                    puzzleCount++;

                    if ((puzzleCount % 50000) == 0) {
                        long sinceStart = System.currentTimeMillis() - start;
                        double secSinceStart = ((double) sinceStart) / 1000.0f;

                        long current = System.currentTimeMillis() - time;
                        double sec = ((double) current) / 1000.0f;

                        System.out.printf("COUNT: %d PUZZLES: %d COLLISIONS: %d NOSOLS: %d 50k: %.2f sec. TOTAL: %.2f\n", count,puzzleCount, exists, noSol,  sec, secSinceStart);
                        for (byte[] arr : puzzleBytes) {
                            fos.write(arr);
                        }
                        fos.flush();

                        puzzleBytes.clear();

                        time = System.currentTimeMillis();
                    }
                }
            }
            for (byte[] arr : puzzleBytes) {
                fos.write(arr);
            }
            fos.flush();
            long sinceStart = System.currentTimeMillis() - start;
            double secSinceStart = ((double) sinceStart) / 1000.0f;
            System.out.printf("COUNT: %d PUZZLES: %d COLLISIONS: %d NOSOLS: %d TOTAL: %.2f\n", count, puzzleCount, exists, noSol, secSinceStart);
            System.out.printf("Wrote %d puzzles to %s.\n", puzzleCount, outName);

            fos.close();
        } else if (arg.equals("parsesols")) {
            String filename = args[1];
            PuzzleIterator p = new PuzzleIterator(filename);

            int puzzles = 0;
            long time = System.currentTimeMillis();
            while (p.hasNext()) {
                Puzzle puzzle = p.next();
                puzzles++;

                int hardness = h.puzzleEasiness(map, puzzle.getSteps());

                if ((puzzles % 1000000) == 0) {
                    long current = System.currentTimeMillis() - time;
                    System.out.printf("Million puzzles in %dms.\n", current);
                    time = System.currentTimeMillis();
                }
            }
            System.out.println(puzzles);
        }
    }
}
