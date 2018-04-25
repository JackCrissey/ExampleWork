import java.util.Random;

public class RandomPlayer {
    int matchesFound;

    public RandomPlayer() {
        matchesFound = 0;
    }

    public Card[] turn(boolean[][]matchFoundArray){
        Card randomCard1 = randomCard(matchFoundArray);
        Card randomCard2 = randomCard2(matchFoundArray, randomCard1);
        Card[] cardArray = new Card[2];
        cardArray[0] = randomCard1;
        cardArray[1] = randomCard2;
        return cardArray;
    }

    public Card randomCard(boolean[][]matchFoundArray){
        Random rand = new Random();
        int randRow;
        int randColumn;
        boolean found = true;
        do{
            randRow = rand.nextInt(4);
            randColumn = rand.nextInt(13);
            found = matchFoundArray[randRow][randColumn];
        }while(found);
        return new Card(randRow, randColumn);
    }

    public Card randomCard2(boolean[][]matchFoundArray, Card alreadyPicked){
        Random rand = new Random();
        int randRow;
        int randColumn;
        boolean found = true;
        do{
            randRow = rand.nextInt(4);
            randColumn = rand.nextInt(13);
            found = matchFoundArray[randRow][randColumn];
            if(randRow == alreadyPicked.row && randColumn == alreadyPicked.column){
                found = true;
            }
        }while(found);
        return new Card(randRow, randColumn);
    }
}
