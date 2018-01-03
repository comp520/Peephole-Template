public abstract class Strategy {
    protected Board board;

    public Strategy(Board board){
        super();
    }

    public abstract Move getMove();
}
