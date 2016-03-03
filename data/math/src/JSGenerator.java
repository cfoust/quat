import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Map;

/**
 * Created by caleb on 3/3/16.
 */
public class JSGenerator {
    public static void dumpToFile(WordMap map, ArrayList<Puzzle> puzzles, String filename) throws Exception {
        FileWriter writer = new FileWriter(filename);

        writer.write("var quat = quat || {};\n");
        writer.write("quat.puzzles = [");

        for (Puzzle puzzle : puzzles) {
            ArrayList<String> steps = puzzle.getSteps();
            String start = steps.get(0),
                   end = steps.get(steps.size() - 1);
            int par = steps.size();

            String out = String.format("[\"%s\",\"%s\",%d],", start, end, par);
            writer.write(out);
        }

        writer.write("]\n");
        writer.close();

//        writer.write("quat.dictionary={");
//        for (Map.Entry<String, Word> wordEntry : map.words.entrySet()) {
//            String word = wordEntry.getKey();
//            writer.write(String.format("%s:1,", word));
//        }
//        writer.write("}");
    }
}
