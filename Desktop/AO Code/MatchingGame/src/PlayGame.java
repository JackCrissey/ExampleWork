import java.util.Random;

public class PlayGame {

    private boolean[][] matchFoundArray;
    private String[][] randDeck;
    private RandomPlayer randomPlayer;
    private MemRandPlayer memRandPlayer;
    private int matchesLeft;

    public PlayGame(){
        matchFoundArray = new boolean[4][13];
        for(int i = 0; i < 4; i++) {
            for (int k = 0; k < 13; k++) {
                matchFoundArray[i][k] = false;
            }
        }
        RandomDeckGenerator deckrand = new RandomDeckGenerator();
        randDeck = deckrand.generate();
        randomPlayer = new RandomPlayer();
        memRandPlayer = new MemRandPlayer();
        matchesLeft=26;
    }

    public boolean[][] getMatchFoundArray() {
        return matchFoundArray;
    }

    public String startGame(){
        String returnString = "";
        while (matchesLeft != 0) {
            boolean matchFoundRandom = true;
            do {
                Card card1 = randomPlayer.randomCard(matchFoundArray);
                card1.cardName = randDeck[card1.row][card1.column];
                Card card2 = randomPlayer.randomCard2(matchFoundArray, card1);
                card2.cardName = randDeck[card2.row][card2.column];
                returnString = returnString + generateOutputTable(card1, card2);
                matchFoundRandom = turn(card1.row, card1.column, card2.row,card2.column);
                if(matchFoundRandom){
                    matchesLeft--;
                    matchFoundArray[card1.row][card1.column]=true;
                    matchFoundArray[card2.row][card2.column]=true;
                    memRandPlayer.removeFromMemArray(card1);
                    memRandPlayer.removeFromMemArray(card2);
                    returnString = returnString + "Congrats! You matched the cards " + randDeck[card1.row][card1.column] + " and " +randDeck[card2.row][card2.column] + "\n\n";
                    randomPlayer.matchesFound++;
                } else {
                    returnString = returnString + "Miss\n\n";
                    matchFoundRandom = false;
                    memRandPlayer.addToMemArray(card1);
                    memRandPlayer.addToMemArray(card2);
                }
                if(matchesLeft == 0){
                    matchFoundRandom = false;
                }
            } while (matchFoundRandom);
            boolean matchFoundMem = true;
            if(matchesLeft != 0) {
                do {
                    Card card1 = memRandPlayer.randomCard(matchFoundArray);
                    card1.cardName = randDeck[card1.row][card1.column];
                    Card card2 = memRandPlayer.memoryCard(matchFoundArray, card1);
                    card2.cardName = randDeck[card2.row][card2.column];
                    returnString = returnString + generateOutputTable(card1, card2);
                    matchFoundMem = turn(card1.row, card1.column, card2.row, card2.column);
                    if (matchFoundMem) {
                        matchesLeft--;
                        matchFoundArray[card1.row][card1.column] = true;
                        matchFoundArray[card2.row][card2.column] = true;
                        memRandPlayer.removeFromMemArray(card1);
                        memRandPlayer.removeFromMemArray(card2);
                        returnString = returnString + "Congrats! You matched the cards " + randDeck[card1.row][card1.column] + " and " + randDeck[card2.row][card2.column] + "\n\n";
                        memRandPlayer.matchesFound++;
                    } else {
                        returnString = returnString + "Miss\n\n";
                        matchFoundMem = false;
                        if(memRandPlayer.memArraySize() == 0){
                            memRandPlayer.addToMemArray(card2);
                        }
                        memRandPlayer.addToMemArray(card1);
                    }
                    if (matchesLeft == 0) {
                        matchFoundMem = false;
                    }
                } while (matchFoundMem);
            }
        }
        if(randomPlayer.matchesFound > memRandPlayer.matchesFound){
            returnString += "Player 1 wins with "+randomPlayer.matchesFound+" matches\n\n";
        } else if(randomPlayer.matchesFound < memRandPlayer.matchesFound){
            returnString += "Player 2 wins with "+memRandPlayer.matchesFound+" matches\n\n";
        } else if(randomPlayer.matchesFound == memRandPlayer.matchesFound){
            returnString += "It was a tie"+"\n\n";
        }
        return returnString;
    }

    public boolean turn(int row1, int column1, int row2, int column2){
        String card1 = randDeck[row1][column1];
        String card2 = randDeck[row2][column2];
        if(card1.charAt(0) == card2.charAt(0)){
            if((card1.charAt(1) == 'D' && card2.charAt(1) == 'H')||(card1.charAt(1) == 'H' && card2.charAt(1) == 'D')) {
                return true;
            } else if ((card1.charAt(1) == 'S' && card2.charAt(1) == 'C')||(card1.charAt(1) == 'C' && card2.charAt(1) == 'S')){
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public String generateOutputTable(Card card1, Card card2){
        String table = "";
        for(int i = 0; i < 4; i++){
            for(int k = 0; k < 13; k++){
                if(matchFoundArray[i][k]){
                    table = table + "XX ";
                } else if(i == card1.row && k == card1.column){
                    table = table + randDeck[i][k] + " ";
                } else if(i == card2.row && k == card2.column){
                    table = table + randDeck[i][k] + " ";
                } else {
                    table = table + "OO ";
                }
            }
            table = table + "\n";
        }
        table = table + "\n";
        return table;
    }
}
