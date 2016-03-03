import java.util.ArrayList;

/**
 * Created by caleb on 3/2/16.
 */
public class PuzzleGenerator {
    WordMap map;
    HeuristicSet set;
    int FREQUENCY_THRESHOLD,
        HARDNESS_THRESHOLD;

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

    public PuzzleGenerator(WordMap map, HeuristicSet set, int FREQUENCY_THRESHOLD, int HARDNESS_THRESHOLD) {
        this.map = map;
        this.set = set;
        this.FREQUENCY_THRESHOLD = FREQUENCY_THRESHOLD;
        this.HARDNESS_THRESHOLD = HARDNESS_THRESHOLD;
    }

    private boolean banned(String word) {
        for (String bad : banned) {
            if (word.equals(bad)) {
                return true;
            }
        }
        return false;
    }

    private String randomAboveHardness() {
        String word = map.randomWord();

        while ((set.wordEasiness(map, word) < HARDNESS_THRESHOLD) ||
                (map.get(word).getFrequency() < FREQUENCY_THRESHOLD) ||
                banned(word)) {
            word = map.randomWord();
        }

        return word;
    }

    public ArrayList<String> generatePuzzle() {
        String first = randomAboveHardness(),
                second = randomAboveHardness();

        while (first == second) {
            second = randomAboveHardness();
        }

        return map.solve(first, second);
    }
}
