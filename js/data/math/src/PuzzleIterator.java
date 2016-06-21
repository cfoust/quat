import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by Caleb on 3/4/2016.
 */
public class PuzzleIterator implements Iterator {
    FileInputStream file;
    public PuzzleIterator(String filename) throws FileNotFoundException {
        file = new FileInputStream(filename);
    }

    @Override
    public boolean hasNext() {
        boolean out = false;

        // Try to read a byte from the file
        try {
            int result = file.read();

            // If it's the start byte, say we have a puzzle
            if (result == 26) {
                out = true;
            }
        } catch (Exception e) {
        }

        if (!out) {
            try {
                file.close();
            } catch (Exception e) {

            }
        }
        return out;
    }

    @Override
    public Puzzle next() {
        int pos = 1;
        byte[] arr = new byte[40];

        // Set up the start byte
        arr[0] = 26;

        // Copy in the byte array
        while (true) {
            int b = -1;

            try {
                b = file.read();
            } catch (IOException e) {
                e.printStackTrace();
            }

            arr[pos] = (byte) b;
            pos++;

            if (b == 27) {
                break;
            }
        }

        return Puzzle.fromBytes(arr);
    }
}
