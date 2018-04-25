import java.util.ArrayList;
import java.util.Random;

public class MemRandPlayer {
    private ArrayList<Card> memArray;
    int matchesFound;

    public MemRandPlayer(){
        matchesFound = 0;
        memArray = new ArrayList<>();
    }

    public Card[] turn(boolean[][]matchFoundArray){
        Card randomCard = randomCard(matchFoundArray);
        Card memCard;
        if(memArray.size() != 0){
            memCard = memoryCard(matchFoundArray, randomCard);
        }else{
            memCard = randomCard(matchFoundArray);
        }
        Card[] cardArray = new Card[2];
        cardArray[0] = randomCard;
        cardArray[1] = memCard;
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

    public Card memoryCard(boolean[][] matchFoundArray, Card card1){
        Random random = new Random();

        if(memArray.size() == 0){
            return randomCard2(matchFoundArray, card1);
        } else {

            String name = card1.cardName;
            int indexOfRepeatCard = -1;
            boolean repeatCardExists = false;
            for(int i=0; i < memArray.size(); i++) {
                String arrayCard = memArray.get(i).cardName;
                if (name.charAt(0) == arrayCard.charAt(0)) {
                    if(name.equals(arrayCard)){
                        indexOfRepeatCard = i;
                        repeatCardExists = true;
                    }
                    if (((name.charAt(1) == 'D' && arrayCard.charAt(1) == 'H') || (name.charAt(1) == 'H' && arrayCard.charAt(1) == 'D'))
                            && !name.equals(arrayCard)) {
                        return memArray.get(i);
                    } else if (((name.charAt(1) == 'S' && arrayCard.charAt(1) == 'C') || (name.charAt(1) == 'C' && arrayCard.charAt(1) == 'S'))
                            && !name.equals(arrayCard)) {
                        return memArray.get(i);
                    }
                }
            }
            int randMemCard = -1;
            if(repeatCardExists && memArray.size() != 1) {
                do {
                    randMemCard = random.nextInt(memArray.size());
                } while (randMemCard == indexOfRepeatCard);
            } else {
                randMemCard = random.nextInt(memArray.size());
            }
            return memArray.get(randMemCard);
        }
    }

    public void addToMemArray(Card mem){
        if(memArray.size() != 0) {
            boolean isInArray = false;
            for (int i = 0; i < memArray.size(); i++) {
                if (memArray.get(i).row == mem.row && memArray.get(i).column == mem.column) {
                    isInArray = true;
                }
            }
            if(!isInArray){
                memArray.add(mem);
            }
        } else {
            memArray.add(mem);
        }
    }

    public void removeFromMemArray(Card mem){
        for (int i = 0; i < memArray.size(); i++) {
            if (memArray.get(i).row == mem.row && memArray.get(i).column == mem.column) {
                memArray.remove(i);
            }
        }
    }

    public int memArraySize(){
        return memArray.size();
    }
}
