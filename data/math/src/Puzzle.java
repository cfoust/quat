import java.util.ArrayList;

/**
 * Created by caleb on 3/2/16.
 */
public class Puzzle {
    private ArrayList<String> steps;
    private int difficulty;

    public Puzzle(ArrayList<String> steps, int difficulty) {
        this.steps = steps;
        this.difficulty = difficulty;
    }

    public ArrayList<String> getSteps() {
        return steps;
    }

    public boolean equals(Puzzle other) {
        ArrayList<String> otherSteps = other.getSteps();
        return (steps.get(0).equals(otherSteps.get(0))) && (steps.get(steps.size() - 1).equals(otherSteps.get(otherSteps.size() - 1)));
    }

    public int getDifficulty() {
        return difficulty;
    }
}
