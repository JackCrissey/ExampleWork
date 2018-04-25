import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Random;

public class MatchingMain {
    public static void main(String[] args) {
        Random rand = new Random();
        int numGames = rand.nextInt(40);
        String output = "";
        for(int i = 0; i < numGames; i++) {
            PlayGame playGame = new PlayGame();
            String returned = playGame.startGame();
            output = output + returned;
        }
        try {
            PrintWriter fileWrite = new PrintWriter(new FileOutputStream("game.txt"));

            fileWrite.println(output);

            fileWrite.close();
        }
        catch(FileNotFoundException stream)
        {
            System.err.println("Could not find file game.txt");
        }
    }

}