import joos.lib.JoosIO;
import java.util.Vector;

/* The Connect4 Board. */
public class Board {
    // The game board, a Vector of Vectors of Characters
    protected Vector columns;
    protected int width;
    protected int height;

    protected Character SPACE;

    public Board(int w, int h) {
        super();
        int x;
        int y;
        Vector column;
        SPACE = new Character(' ');
        width = w;
        height = h;
        columns = new Vector(width);
        for (x = 0; x < width; x++) {
            column = new Vector(height);
            for (y = 0; y < height; y++)
                column.addElement(SPACE);
            columns.addElement(column);
        }
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public Character get(int col, int row) {
        Vector column;
        column = (Vector)(columns.elementAt(col));
        return (Character)(column.elementAt(row));
    }

    public boolean full() {
        int row;
        int col;
        for (row = 0; row < height; row++)
            for (col = 0; col < width; col++)
                if (this.get(col, row) == SPACE)
                    return false;
        return true;
    }

    // Should be private
    public boolean inRange(int col, int row) {
        return 0 <= col && col < width && 0 <= row && row < height;
    }

    // Should be private
    public void set(int col, int row, Character c) {
        if (this.inRange(col, row))
            ((Vector)columns.elementAt(col)).setElementAt(c, row);
    }

    public void place(int col, Character c) {
        if (this.isValidColumn(col))
            this.set(col, this.expectedRow(col), c); 
    }

    // Some of the special moves delete cells from the board using this.
    public void clear(int col, int row) {
        this.set(col, row, SPACE);
    }

    // Should be private
    // Some special moves delete cells from the board, possibly creating gaps
    // This makes all the pieces "fall down"
    public void normalize() {
        int row;
        int i;
        
        for (i = 0; i < height; i++) {
            for (row = 0; row < height - 1; row++) {
                int col;
                for (col = 0; col < width; col++) {
                    if (this.get(col, row) == SPACE && this.get(col, row + 1) != SPACE) {
                        this.set(col, row, this.get(col, row + 1));
                        this.set(col, row + 1, SPACE);
                    }
                }
            }
        }
    }

    // Should be private
    public int expectedRow(int col) {
        int row;
        if (!(0 <= col && col < width))
            return height;
        for (row = height - 1; row >= 0; row = row - 1) {
            if (this.get(col, row) != SPACE) 
                return row + 1;
        }
        return 0;
    }

    public boolean isValidColumn(int col) {
        return 0 <= col && col < width && this.expectedRow(col) != height;
    }

    public void print() {
        JoosIO j;
        int row;
        int col;
        j = new JoosIO();
        for (col = 0; col < width; col++)
            j.print("|---");
        j.println("|");
        for (row = height - 1; row >= 0; row = row - 1) {
            for (col = 0; col < width; col++) {
                j.print("| ");
                j.print(this.get(col, row).toString());
                j.print(" ");
            }
            j.println("|");
            for (col = 0; col < width; col++)
                j.print("|---");
            j.println("|");
        }
    }

    public Character getWinner() {
        int row;
        int col;
        boolean changed;
        int i;
        // horizontal wins
        for (row = 0; row < height; row++) {
            for (col = 0; col < width - 4; col++) {
                changed = false;
                for (i = col + 1; i < col + 4; i++)
                    if (this.get(i - 1, row) != this.get(i, row))
                        changed = true;
                if (!changed && this.get(col, row) != SPACE)
                    return this.get(col, row);
            }
        }
        // vertical wins
        for (col = 0; col < width; col++) {
            for (row = 0; row < height - 4; row++) {
                changed = false;
                for (i = row + 1; i < row + 4; i++)
                    if (this.get(col, i -1) != this.get(col, i))
                        changed = true;
                if (!changed && this.get(col, row) != SPACE)
                    return this.get(col, row);
            }
        }
        // / diagonal wins
        for (row = 0; row < height - 3; row++) {
            for (col = 0; col < height - 3; col++) {
                changed = false;
                for (i = 0; i < 4; i++)
                    if (this.get(col + i, row + i) != this.get(col, row))
                        changed = true;
                if (!changed && this.get(col, row) != SPACE)
                    return this.get(col, row);
            }
        }

       // \ diagonal wins
       for (row = height - 1; row >= 3; row = row - 1) {
            for (col = 0; col < width - 4; col++) {
                changed = false;
                for (i = 0; i < 4; i++)
                    if (this.get(col + i, row - i) != this.get(col, row))
                        changed = true;
                if (!changed && this.get(col, row) != SPACE)
                    return this.get(col, row);
            }
        }  
        // no winner
        return null;
    }                                  

    public static void main (String [] args)
    {
        Board b;
        JoosIO io;
        io = new JoosIO();
        b = new Board(7, 7);
        b.print();
        b.set(6, 6, new Character('X'));
        b.set(6, 5, new Character('O'));
        b.print();
        b.normalize();
        b.print();
    }
}
