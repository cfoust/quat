import java.util.ArrayList;
import java.util.Collections;

/**
 * Created by caleb on 3/2/16.
 */
public class Puzzle {
    private ArrayList<String> steps;

    public Puzzle(ArrayList<String> steps) {
        this.steps = steps;
    }
    public Puzzle(String start, String finish) {
        steps = new ArrayList<>();
        steps.add(start);
        steps.add(finish);
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

    public void cutOutSolution() {
        while (steps.size() > 2) {
            steps.remove(1);
        }
    }

    public String toString() {
        String start = "";
        for (int i = 0; i < steps.size(); i++) {
            start += steps.get(i);
            if (i != steps.size() - 1) {
                start += "->";
            }
        }
        return start;
    }

    public byte[] toBytes() {
        /*
        2 is the start and end puzzle bytes.
        4 is the four letters of the first word.
        1 less from steps size because we don't need to include the first word.
         */
        int size = 2 + 4 + steps.size() - 1;
        byte[] bytes = new byte[size];
        bytes[0] = 26; // Start byte

        String start = getFirst();
        for (int i = 0; i < 4; i++) {
            // Converts the char into a value from 0-25
            bytes[i + 1] = (byte) (start.charAt(i) - 97);
        }

        for (int i = 1; i < steps.size(); i++) {
            String word = steps.get(i),
                   prev = steps.get(i-1);

            byte pos = -1;
            byte c = -1;
            for (int j = 0; j < 4; j++) {
                if (prev.charAt(j) != word.charAt(j)) {
                    pos = (byte) j;
                    c = (byte) (word.charAt(j) - 97);
                    break;
                }
            }
            bytes[i + 4] = (byte) ((pos << 5) + c);
        }

        bytes[size - 1] = 27; // End byte

        return bytes;
    }

    public static Puzzle fromBytes(byte[] bytes) {
        // Parse out the word
        String word = "";
        for (int i = 0; i < 4; i++) {
            word += String.valueOf((char) ((bytes[i+1]) + 97));
        }

        ArrayList<String> puzzle = new ArrayList<>();
        puzzle.add(word);

        int pos = 5;
        while (true) {
            byte b = bytes[pos];
            int idx = (b >> 5), c = ((idx << 5) ^ b);

            if ((c == 27) || (b == 0)) {
                break;
            }

            String step = "";
            String previous = puzzle.get(pos - 5);
            for (int i = 0; i < 4; i++) {
                if (i == idx) {
                    step += String.valueOf((char) (c + 97));
                } else {
                    step += String.valueOf(previous.charAt(i));
                }
            }
            puzzle.add(step);
            pos++;
        }

        return new Puzzle(puzzle);
    }

    public void reverse() {
        Collections.reverse(steps);
    }

    public boolean equals(Puzzle other) {
        return (getFirst().equals(other.getFirst()) && (getLast().equals(other.getLast()))) ||
               (getFirst().equals(other.getLast()) && (getLast().equals(other.getFirst())));
    }

    @Override
    public int hashCode() {
        return (getFirst().hashCode() + getLast().hashCode());
    }
}
