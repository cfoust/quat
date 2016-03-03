import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

/**
 * Created by caleb on 3/1/16.
 */
public class WordMap {
    public Map<String, Word> words;
    private Random r;

    public WordMap() {
        words = new HashMap<>();
        r = new Random();
    }

    public Word get(String word) {
        return words.get(word);
    }

    public boolean containsWord(String word) {
        return words.get(word) != null;
    }

    public String randomWord() {
        int item = r.nextInt(words.size()),
            i = 0;
        for (Map.Entry<String, Word> obj : words.entrySet()) {
            if (i == item) {
                return obj.getKey();
            }
            i++;
        }
        return null;
    }



    public static WordMap fromFile(String file) throws Exception {
        WordMap map = new WordMap();

        File wordFile = new File(file),
             mapFile = new File(file + ".map");

        if (!wordFile.exists()) {
            throw new Exception("File does not exist");
        }

        // If the mapfile exists, we can just load from that
        if (mapFile.exists()) {
            return WordMap.fromMap(file + ".map");
        }

        // Otherwise we have to recalculate all of this

        BufferedReader br = new BufferedReader(new FileReader(wordFile));
        for (String line = br.readLine(); line != null; line = br.readLine()) {
            // Split each line into parts by space
            String[] parts = line.trim().split("\\s");

            // Invalid line
            if (parts.length != 2) {
                continue;
            }

            map.words.put(parts[0], new Word(parts[0], Integer.parseInt(parts[1])));
        }

        Object[] words = map.words.entrySet().toArray();
        // Iterate over all the words
        for (int i = 0; i < words.length; i++) {
            Word word = (Word) words[i];

            // Iterate over all the other words and check if these two words
            // differ by exactly one letter
            for (int j = 0; j < words.length; j++) {
                Word other = (Word) words[j];
                if (word.differences(other) == 1) {
                    word.addSuccessor(other);
                }
            }
        }

        // Dump it to a map file
        map.toMap(file + ".map");

        return map;
    }

    private static WordMap fromMap(String file) throws IOException {
        WordMap map = new WordMap();

        File mapFile = new File(file);

        BufferedReader br = new BufferedReader(new FileReader(mapFile));

        // Iterate over the map's lines.
        ArrayList<String[]> memoryLines = new ArrayList<>();
        for (String line = br.readLine(); line != null; line = br.readLine()) {
            // Split each line into parts by tab
            String[] parts = line.trim().split("\\t");

            // Invalid line
            if (parts.length == 2) {
                parts = new String[] {parts[0], parts[1], ""};
            }

            // Store the parts in memory
            memoryLines.add(parts);
        }

        /* We store the map's lines in memory because we need to go over them twice and they aren't very big.*/

        // First pass, add all the words
        for (String[] parts : memoryLines) {
            try {
                map.words.put(parts[0], new Word(parts[0], Integer.parseInt(parts[1])));
            } catch (Exception e) {
                continue;
            }
        }

        // Second pass, add all their successors
        for (String[] parts : memoryLines) {
            String[] successors = parts[2].split(",");
            if (successors.length == 0) {
                continue;
            }
            Word word = map.words.get(parts[0]);

            for (String successor : successors) {
                try {
                    word.addSuccessor(map.words.get(successor));
                } catch (Exception e) {
                    continue;
                }
            }
        }

        return map;
    }

    public ArrayList<String> solve(String start, String end) {
        Map<String, WordWrap> graph = new HashMap<>();


        // Build a "copy" of the graph with special places to store data
        for (Object obj : words.values().toArray()) {
            Word word = (Word) obj;
            graph.put(word.getWord(), new WordWrap(word));
        }

        WordWrap startWord = graph.get(start),
                 endWord = graph.get(end);

        Queue<WordWrap> queue = new LinkedList<>();
        queue.add(startWord);

        while(!queue.isEmpty()) {
            WordWrap word = queue.remove();

            // We've hit the goal
            if (word == endWord) {
                ArrayList<String> solution = new ArrayList<>();
                solution.add(word.word.getWord());

                WordWrap current = word;
                while (current != startWord) {
                    WordWrap predecessor = current.predecessor;
                    solution.add(predecessor.word.getWord());
                    current = predecessor;
                }

                // Reverse the solution
                Collections.reverse(solution);

                return solution;
            }

            for (Object obj : word.word.getSuccessors().toArray()) {
                WordWrap successor = graph.get(((Word) obj).getWord());
                if (successor.distance == -1) {
                    // Increase the distance by one
                    successor.distance = word.distance + 1;

                    // Make this word the predecessor
                    successor.predecessor = word;

                    // Add it to the stack
                    queue.add(successor);
                }
            }
        }

        return null;
    }

    private void toMap(String fileName) throws IOException {
        FileWriter writer = new FileWriter(fileName);

        for (Object obj : words.entrySet().toArray()) {
            Word word = (Word) obj;
            String wordString = word.getWord(),
                   freqString = String.valueOf(word.getFrequency()),
                   successorString = "";

            Object[] successors = word.getSuccessors().toArray();
            for (int i = 0; i < successors.length; i++) {
                Word successor = (Word) successors[i];
                String delimeter = (i == successors.length - 1) ? "" : ",";
                successorString += successor.getWord() + delimeter;
            }

            writer.write(wordString + "\t" + freqString + "\t" + successorString);
        }
    }
}
