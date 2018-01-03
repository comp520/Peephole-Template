public class BombMove extends Move {
    public BombMove() {
        super();
    }

    public void apply(int col, int row, Board board, Character currP) {
        int i;
        int j;
        for (i = col-1; i <= col+1; i++) {
            for (j = row-1; j <= row+1; j++) {
                board.clear(i, j);
            }
        }
    }

    public String toString() {
        return "Bomb: eliminates the contents of all surrounding cells.";
    }
}
