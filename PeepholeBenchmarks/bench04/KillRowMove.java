public class KillRowMove extends Move {
    public KillRowMove() {
        super();
    }

    public void apply(int col, int row, Board board, Character currP) {
        int i;
        for (i=0; i < board.getWidth(); i++) {
            board.clear(i, row);
        }
    }

    public String toString() {
        return "Kill Row: clears the row where the token lands.";
    }
}
