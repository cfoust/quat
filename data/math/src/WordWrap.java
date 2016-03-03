/**
 * Created by caleb on 3/1/16.
 */
public class WordWrap {
    public int distance;
    public WordWrap predecessor;
    public Word word;

    public WordWrap(Word word) {
        distance = -1;
        predecessor = null;
        this.word = word;
    }

    public boolean equals(WordWrap other) {
        return word == other.word;
    }

    @Override
    public int hashCode() {
        return word.hashCode();
    }
}
