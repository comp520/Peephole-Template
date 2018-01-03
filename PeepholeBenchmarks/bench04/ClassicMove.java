public class ClassicMove extends Move {
    public ClassicMove() {
        super();
    }

    public void apply(int column, int row, Board board, Character currP) {
       board.place(column, currP);
    }

    public String toString() {
        return "Classic: drops a token in a chosen column.";
    }
}
