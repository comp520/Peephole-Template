public class DiagBombMove extends Move {
    public DiagBombMove() {
        super();
    }

    public void apply(int col, int row, Board board, Character currP) {
        int i;
        int j;
        int width;
        int height;
        width = board.getWidth();
        height = board.getHeight();
        
        j = row-1;
        for(i=col-1; i>=0; i=i-1) {
            if(board.inRange(i, j)) {
                board.clear(i, j);
            }
            j = j-1;
        }

        j = row-1;
        for(i=col+1; i<width; i++) {
            if(board.inRange(i, j)) {
                board.clear(i, j);
            }
            j = j-1;
        }

        j = row+1;
        for(i=col-1; i>=0; i=i-1) {
            if(board.inRange(i, j)) {
                board.clear(i, j);
            }
            j++;
        }

        j = row+1;
        for(i=col+1; i<width; i++) {
            if(board.inRange(i, j)) {
                board.clear(i, j);
            }
            j++;
        }
    }

    public String toString() {
        return "Diagonal Bomb: clears the contents of diagonal cells.";
    }
}
