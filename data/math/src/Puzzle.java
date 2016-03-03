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

    public String getFirst() {
        return steps.get(0);
    }

    public String getLast() {
        return steps.get(steps.size() - 1);
    }

    public boolean equals(Puzzle other) {
        return (getFirst().equals(other.getFirst()) && (getLast().equals(other.getLast()))) ||
               (getFirst().equals(other.getLast()) && (getLast().equals(other.getFirst())));
    }

    @Override
    public int hashCode() {
        return (getFirst() + getLast()).hashCode();
    }

    public int getDifficulty() {
        return difficulty;
    }
}
