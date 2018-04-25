public class Card {
    String cardName;
    int row;
    int column;

    public Card(String cardName, int row, int column) {
        this.cardName = cardName;
        this.row = row;
        this.column = column;
    }

    public Card(int row, int column) {
        this.row = row;
        this.column = column;
    }

    public Card() {
        row = -1;
        column = -1;
        cardName = null;
    }
}
