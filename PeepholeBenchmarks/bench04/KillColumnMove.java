public class KillColumnMove extends Move {
    public KillColumnMove() {
        super();
    }

    public void apply(int col, int row, Board board, Character currP) {
        int i;
        for(i=0; i < board.getHeight(); i++) {
            board.clear(col, i);
        }
    }

    public String toString() {
        return "Kill Column: clears the column where the token lands.";
    }
}
