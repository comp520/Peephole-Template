public abstract class Move {
    public Move() {
        super();
    }
    
    public abstract void apply(int column, int row, Board board, Character currPlayer);
}
