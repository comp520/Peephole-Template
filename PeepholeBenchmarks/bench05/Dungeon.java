import joos.lib.*;
import java.lang.*;

public class Dungeon {

    protected DungeonInfos infos;
    protected Vector output;


    public Dungeon(DungeonInfos i) {
        super();

        infos = i;
        output = new Vector();
    }


    public void draw() {
        JoosIO io;
        int i;
        int j;
        CustomPoint dimension;
        Vector v;

        //output.clear();

        this.createRoom();

        v = infos.getMonsters();
        for (i = 0; i < v.size(); i++)
            this.createItem("M", (CustomPoint) v.elementAt(i));

        v = infos.getUpstairs();
        for (i = 0; i < v.size(); i++)
            this.createItem("U", (CustomPoint) v.elementAt(i));

        v = infos.getDownstairs();
        for (i = 0; i < v.size(); i++)
            this.createItem("D", (CustomPoint) v.elementAt(i));

        v = infos.getTreasures();
        for (i = 0; i < v.size(); i++)
            this.createItem("T", (CustomPoint) v.elementAt(i));

        v = infos.getHeros();
        for (i = 0; i < v.size(); i++)
            this.createItem("H", (CustomPoint) v.elementAt(i));

        io = new JoosIO();

        dimension = infos.getDimension();

        for (i = 0; i < dimension.getY() + 2; i++) {
            for (j = 0; j < dimension.getX() + 2; j++) {
                io.print(((Vector) output.elementAt(i)).elementAt(j).toString());
            }

            io.println("");
        }
    }


    public void createRoom() {
        int i;
        int j;
        CustomPoint dimension;
        Vector v;

        dimension = infos.getDimension();

        for (i = 0; i < dimension.getY() + 2; i++) {
            v = new Vector();

            for (j = 0; j < dimension.getX() + 2; j++) {
                if ((i == 0 && j == 0) ||
                    (i == dimension.getY() + 1 && j == 0) ||
                    (i == 0 && j == dimension.getX() + 1) ||
                    (i == dimension.getY() + 1 && j == dimension.getX() + 1))
                    v.addElement("+");
                else if (i == 0 || i == dimension.getY() + 1)
                    v.addElement("-");
                else if (j == 0 || j == dimension.getX() + 1)
                    v.addElement("|");
                else
                    v.addElement(" ");
            }

            output.addElement(v);
        }
    }


    public void createItem(String representation, CustomPoint position) {
        Vector line;

        line = (Vector) output.elementAt(position.getY());

        line.setElementAt(representation, position.getX());
    }
}
