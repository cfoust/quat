import java.util.ArrayList;

/**
 * Created by caleb on 3/1/16.
 */
public interface HeuristicSet {
    int wordEasiness(WordMap map, String word);
    int puzzleEasiness(WordMap map, ArrayList<String> solution);
}
