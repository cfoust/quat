import java.util.ArrayList;

/**
 * Created by caleb on 3/1/16.
 */
public class Word {
    // The word itself
    private String word;

    // The frequency of the word
    private int frequency;

    private ArrayList<Word> successors;

    public Word(String word, int frequency) throws Exception {
        // If the word is of invalid length, throw an exception
        if (word.length() != 4) {
            throw new Exception("Cannot initialize word longer than four letters.");
        }

        this.word = word;
        this.frequency = frequency;
        this.successors = new ArrayList<>();
    }

    /**
     * Gets the differences between this word and another word. A difference is where two letters in similar positions
     * are not the same letter.
     * @param other The other word.
     * @return Number of differences.
     */
    int differences(Word other) {
        int differences = 0;
        String otherWord = other.getWord();

        // Calculate how many differences there are between the two words
        for (int i = 0; i < 4; i++) {
            if (otherWord.charAt(i) != word.charAt(i)) {
                differences++;
            }
        }

        return differences;
    }

    /**
     * Adds a reference to a successor to this word.
     * @param successor
     */
    void addSuccessor(Word successor) throws Exception {
        if (differences(successor) != 1) {
            throw new Exception("Successor is more than one letter different from this word");
        }

        successors.add(successor);
    }

    /**
     * Gets the frequency of this word. Should always be positive.
     * @return Positive integer frequency of node.
     */
    int getFrequency() {
        return frequency;
    }

    /**
     * Gets this word's successors.
     * @return ArrayList populated by this word's successors.
     */
    ArrayList<Word> getSuccessors() {
        return successors;
    }

    /**
     * Returns this Word's four-letter word.
     * @return
     */
    String getWord() {
        return word;
    }

    public boolean equals(Word other) {
        return word.equals(other.getWord());
    }

    @Override
    public int hashCode() {
        return word.hashCode();
    }
}
