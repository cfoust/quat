import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import java.util.Set;

/**
 * Created by caleb on 3/1/16.
 */
public class MathApp {
    public static void main(String[] args) throws Exception {
        // Load up the wordmap from a file (compiles it into a .map if necessary)
        WordMap map = WordMap.fromFile("../words");

        Set<Map.Entry<String, Word>> wordEntries = map.words.entrySet();

        ArrayList<Word> words = new ArrayList<>();
        for (Map.Entry<String, Word> entry : wordEntries) {
            words.add(entry.getValue());
        }

        int puzzleCount = 0;
        HashMap<String, Puzzle> puzzles = new HashMap<>();

        long time = System.currentTimeMillis();

        for (int i = 0; i < words.size(); i++) {
            Word word = words.get(i);
            for (int j = 0; j < words.size(); j++) {
                if (i == j) continue;
                Word other = words.get(j);

                String first = word.getWord() + other.getWord(),
                       second = other.getWord() + word.getWord();

                if ((puzzles.get(first) != null) || (puzzles.get(second) != null)) {
                    continue;
                }

                puzzles.put(first, new Puzzle(map.solve(word.getWord(), other.getWord()), 0));

                puzzleCount++;

                if (puzzleCount == 1000) {
                    long diff = System.currentTimeMillis() - time;
                    System.out.printf("Took %d milliseconds to solve 1000 puzzles\n", diff);
                    break;
                }
            }
            break;
        }
//        System.out.printf("%d total puzzles.\n", puzzleCount);

    }
}
