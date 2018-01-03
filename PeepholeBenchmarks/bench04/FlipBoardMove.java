public class FlipBoardMove extends Move {
    public FlipBoardMove() {
        super();
    }

    public void apply(int col, int row, Board board, Character currP) {
        int i;
        int j;
        int width;
        int height;
        Character currChar;
        Board flipBoard;
        width = board.getWidth();
        height = board.getHeight();
        flipBoard = new Board(width, height);
        
        for(i = 0; i < width; i++) {
            for(j = height-1; j >= 0; j = j-1) {
                currChar = board.get(i, j);
                flipBoard.place(i, currChar);
            }
        }

        for(i=0; i<width; i++) {
            for(j=0; j<height; j++) {
                board.set(i, j, flipBoard.get(i, j));
            }
        }
    }

    public String toString() {
        return "Flip Board: flips the board upside down.";
    }
}
