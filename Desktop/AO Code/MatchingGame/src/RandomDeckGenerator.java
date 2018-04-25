import java.util.Random;

public class RandomDeckGenerator {
    String[][] deck;

    public RandomDeckGenerator(){
        deck = new String[4][13];
        deck[0][0]="AD";
        deck[0][1]="2D";
        deck[0][2]="3D";
        deck[0][3]="4D";
        deck[0][4]="5D";
        deck[0][5]="6D";
        deck[0][6]="7D";
        deck[0][7]="8D";
        deck[0][8]="9D";
        deck[0][9]="TD";
        deck[0][10]="JD";
        deck[0][11]="QD";
        deck[0][12]="KD";
        deck[1][0]="AH";
        deck[1][1]="2H";
        deck[1][2]="3H";
        deck[1][3]="4H";
        deck[1][4]="5H";
        deck[1][5]="6H";
        deck[1][6]="7H";
        deck[1][7]="8H";
        deck[1][8]="9H";
        deck[1][9]="TH";
        deck[1][10]="JH";
        deck[1][11]="QH";
        deck[1][12]="KH";
        deck[2][0]="AS";
        deck[2][1]="2S";
        deck[2][2]="3S";
        deck[2][3]="4S";
        deck[2][4]="5S";
        deck[2][5]="6S";
        deck[2][6]="7S";
        deck[2][7]="8S";
        deck[2][8]="9S";
        deck[2][9]="TS";
        deck[2][10]="JS";
        deck[2][11]="QS";
        deck[2][12]="KS";
        deck[3][0]="AC";
        deck[3][1]="2C";
        deck[3][2]="3C";
        deck[3][3]="4C";
        deck[3][4]="5C";
        deck[3][5]="6C";
        deck[3][6]="7C";
        deck[3][7]="8C";
        deck[3][8]="9C";
        deck[3][9]="TC";
        deck[3][10]="JC";
        deck[3][11]="QC";
        deck[3][12]="KC";
    }

    public String[][] generate(){
        String[][] randDeck = new String[4][13];
        Boolean[][] cardUsedArray = new Boolean[4][13];
        for(int i = 0; i < 4; i++) {
            for (int k = 0; k < 13; k++) {
                cardUsedArray[i][k] = false;
            }
        }
        for(int i = 0; i < 4; i++){
            for(int k = 0; k < 13; k++){
                Random rand = new Random();
                int randSuite = 0;
                int randNum = 0;
                Boolean cardUsed = true;
                do{
                    randSuite = rand.nextInt(4);
                    randNum = rand.nextInt(13);
                    cardUsed = cardUsedArray[randSuite][randNum];
                }while(cardUsed);
                cardUsedArray[randSuite][randNum] = true;
                randDeck[i][k] = deck[randSuite][randNum];
            }
        }
        return randDeck;
    }
}
