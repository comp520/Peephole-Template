import joos.lib.*;

public class DungeonInfos {
    protected CustomPoint dimension;
    protected Vector monsters;
    protected Vector upstairs;
    protected Vector downstairs;
    protected Vector treasures;
    protected Vector heros;


    public DungeonInfos() {
        super();

        this.initializeTo0();
    }


    public void initializeTo0() {
        dimension = new CustomPoint();
        monsters = new Vector();
        upstairs = new Vector();
        downstairs = new Vector();
        treasures = new Vector();
        heros = new Vector();
    }


    public void initializeFromStdIn() {
        JoosIO io;
        String type;
        int x;
        int y;

        io = new JoosIO();

        type = io.readLine();

        //io.println(type);

        while (type != null && !type.equals("")) {

            x = io.readInt();
            y = io.readInt();

            if (type.equals("Room"))
                dimension = new CustomPoint(x, y);
            if (type.equals("Monster"))
                monsters.addElement(new CustomPoint(x, y));
            else if (type.equals("Upstairs"))
                upstairs.addElement(new CustomPoint(x, y));
            else if (type.equals("Downstairs"))
                downstairs.addElement(new CustomPoint(x, y));
            else if (type.equals("Treasure"))
                treasures.addElement(new CustomPoint(x, y));
            else if (type.equals("Hero"))
                heros.addElement(new CustomPoint(x, y));

            type = io.readLine();
        }
    }


    public CustomPoint getDimension() {
        return dimension;
    }


    public Vector getMonsters() {
        return monsters;
    }


    public Vector getUpstairs() {
        return upstairs;
    }


    public Vector getDownstairs() {
        return downstairs;
    }


    public Vector getTreasures() {
        return treasures;
    }


    public Vector getHeros() {
        return heros;
    }
}
