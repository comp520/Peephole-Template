import java.util.Vector;
import joos.lib.JoosIO;
import java.util.Random;

public class Game {
    protected Board board;
    protected Character X;
    protected Character O;
    protected Character currentPlayer;
    protected Vector moves;
    protected Vector playerXMoves;
    protected Vector playerOMoves;
    protected int maxSpecialtyMoves;

    public Game(Board b) {
        super();
        board = b;
        X = new Character('X');
        O = new Character('O');
        currentPlayer = X;
        moves = new Vector();
        playerXMoves = new Vector();
        playerOMoves = new Vector();
        maxSpecialtyMoves = 3;

    }

    public void fillPlayerMovesNormalMode(Vector vec) {
        vec.addElement(new ClassicMove());
        vec.addElement(new BombMove());
        vec.addElement(new KillRowMove());
        vec.addElement(new FlipBoardMove());
    }

    public void fillMoves(Vector vec){
        vec.addElement(new ClassicMove());
        vec.addElement(new BombMove());
        vec.addElement(new DiagBombMove());
        vec.addElement(new KillRowMove());
        vec.addElement(new KillColumnMove());
        vec.addElement(new KillRowAndColumnMove());
        vec.addElement(new FlipBoardMove());
    }

    public void setSpecialtyMoves(Vector playerMoves) {
        int i;
        int rdmNum;
        Random rdm;
        Vector tmpMoves;
        
        rdm = new Random();
        tmpMoves = new Vector();
        rdmNum = 0;
        playerMoves.addElement(new ClassicMove());
        this.fillMoves(tmpMoves);

        for(i=0; i<maxSpecialtyMoves; i++) {
            while(rdmNum == 0) {
                rdmNum = rdm.nextInt(tmpMoves.size());
            }
            playerMoves.addElement(tmpMoves.elementAt(rdmNum));
            tmpMoves.removeElementAt(rdmNum);
            rdmNum = 0;
        }
    }

    /* These functions might come in handy for Move classes. */
    public Character getX() {
        return X;
    }

    public Character getO() {
        return O;
    }
    
    public Character getCurrentPlayer() {
        return currentPlayer;
    }

    public Character getOtherPlayer() {
        if (currentPlayer == X)
            return O;
        return X;
    }

    public Character getOpponent(Character player) {
        if (player == X)
            return O;
        return X;
    }

    public void togglePlayer() {
        if (currentPlayer == X)
            currentPlayer = O;
        else
            currentPlayer = X;
    }

    public Vector getCurrPlayerMoves() {
        if (this.getCurrentPlayer() == this.getX()) {
            return playerXMoves;
        }
        return playerOMoves;
    }

    public void printMenu() {
        JoosIO io;
        int i;
        int j;
        Vector currPlayerMoves;
        io = new JoosIO();
        currPlayerMoves = this.getCurrPlayerMoves();
        for(i=0; i<currPlayerMoves.size(); i++) {
            j = i+1;
            io.println(j + " - " + (currPlayerMoves.elementAt(i)).toString());
        }
    }

    public void doMove() {
        Vector currPlayerMoves;
        JoosIO io;
        String userInput;
        boolean validChoice;
        int choice;
        currPlayerMoves = this.getCurrPlayerMoves();
        io = new JoosIO();
        validChoice = false;
        choice = 0;
        
        io.println("Player " + this.getCurrentPlayer() + "'s turn -> What would you like to do?");
        this.printMenu();
        
        while (!validChoice) {
                choice = io.readInt();
                if (choice > 0 && choice <= currPlayerMoves.size()) {
                    validChoice = true;
                } else {
                    io.println("Invalid choice, please choose again:");
                    this.printMenu();
                }
        }
        this.applyMove(choice-1);
    }

    public int getColumnChoice() {
        JoosIO io;
        int choice;
        int maxChoice;
        boolean validChoice;
        String userInput;
        io = new JoosIO();
        maxChoice = board.getWidth();
        validChoice = false;
        choice = 0;

        io.println("Please choose a column between 1 and " + maxChoice);

        while(!validChoice) {
            choice = io.readInt();
            if (!(choice > 0 && choice <= maxChoice)) {
                io.println("Invalid column choice, please choose a column number between 1 and " + maxChoice + ":");
            }
            if (!board.isValidColumn(choice-1)) {
                io.println("Error: column is full, please choose again:");
            } else {
                validChoice = true;
            }
        }
        return choice-1;        
    }

    public void applyMove(int choice) {
        int col;
        int row;
        Vector currMoves;
        Move move;
        col = this.getColumnChoice();
        row = board.expectedRow(col);
        currMoves = this.getCurrPlayerMoves();
        move = (Move)(currMoves.elementAt(choice));
        move.apply(col, row, board, this.getCurrentPlayer());
        if (choice != 0) { //Never remove Classic move
            this.getCurrPlayerMoves().removeElementAt(choice);
        }
        board.normalize();
    }

    public void printGameModeMenu() {
        JoosIO io;
        io = new JoosIO();

        io.println("1 - with fixed specialty moves\n2 - with random specialty moves");
    }

    public void initGameMode() {
        JoosIO io;
        int choice;
        boolean validChoice;

        io = new JoosIO();
        validChoice = false;
        choice = 0;

        io.println("\nThank you for playing BATTLE CONNECT FOUR!\n");
        io.println("Before starting, please choose a game mode:");
        this.printGameModeMenu();

        while (!validChoice) {
                choice = io.readInt();
                if (choice == 1 || choice == 2) {
                    validChoice = true;
                } else {
                    io.println("Invalid choice, please choose again:");
                    this.printGameModeMenu();
                }
        }

        this.fillMoves(moves);
        if (choice == 1) {
            this.fillPlayerMovesNormalMode(playerXMoves);
            this.fillPlayerMovesNormalMode(playerOMoves);
        } else {
            this.setSpecialtyMoves(playerXMoves);
            this.setSpecialtyMoves(playerOMoves);
        }
    }

    public Character play() {
        JoosIO io;
        Character winner;
        io = new JoosIO();
        winner = null;
        this.initGameMode();
        while (winner == null && !board.full()) {
            board.print();
            this.doMove();
            winner = board.getWinner();
            this.togglePlayer();
        }
        io.println("GAME OVER!!!");
        board.print();
        return winner;
    }

    public static void main(String[] args) {
        JoosIO io;
        Game game;
        Character winner;
        io = new JoosIO();
        game = new Game(new Board(7, 7));
        winner = game.play();
        if (winner == null)
            io.println("Stalemate!");
        else
            io.println("Winner: " + winner.toString());
    }
}
