public class KillRowAndColumnMove extends Move {
    public KillRowAndColumnMove() {
        super();
    }

    public void apply(int col, int row, Board board, Character currP) {
        int i;
        int j;

        for(i=0; i < board.getWidth(); i++) {
            board.clear(i, row);
        }

        for(j=0; j < board.getHeight(); j++) {
            board.clear(col, j);
        }
    }

    public String toString() {
        return "Kill Row & Column: clears the row and column where the token lands.";
    }
}
