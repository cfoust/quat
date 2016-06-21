import java.util.ArrayList;

/**
 * Created by caleb on 3/1/16.
 */
public class ThreshHeuristic implements HeuristicSet {

    int threshold;
    public ThreshHeuristic(int threshold) {
        this.threshold = threshold;
    }

    int metricForWord(Word word) {
        return (int) Math.min(Math.ceil((float) word.getFrequency() / (float) threshold), 100);
    }

    @Override
    public int wordEasiness(WordMap map, String word) {
        Word wordObj = map.get(word);

        int sum = 0;
        for (Word succ : wordObj.getSuccessors()) {
            sum += metricForWord(succ);
        }

        return sum;
    }

    @Override
    public int puzzleEasiness(WordMap map, ArrayList<String> solution) {
        int startEasiness = wordEasiness(map, solution.get(0)),
            endEasiness = wordEasiness(map, solution.get(solution.size() - 1)),
            totalEasiness = startEasiness + endEasiness;

        float val = (float) totalEasiness / 200.0f;

        return (int) ((solution.size() - val) * 100) + 300;
    }
}
