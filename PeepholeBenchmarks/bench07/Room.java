import joos.lib.*;

public class Room {
    protected String description;
    protected Room north;
    protected Room south;
    protected Room west;
    protected Room east;
    protected RoomAction action;
    protected JoosIO io;

    public Room(Room source, String direction, int depth)
    {
        super();
        int special;
        int d;

        io = new JoosIO();
        d = depth - 1;
        north = null;
        south = null;
        west = null;
        east = null;

        if (depth > 0)
        {
            if (direction.equals("south"))
            {
                north = source;
            }
            else if (this.randomRange(10) < depth)
            {
                north = new Room(this, "north", d);
            }
            if (direction.equals("north"))
            {
                south = source;
            }
            else if (this.randomRange(10) < depth)
            {
                south = new Room(this, "south", d);
            }
            if (direction.equals("west"))
            {
                east = source;
            }
            else if (this.randomRange(10) < depth)
            {
                east = new Room(this, "east", d);
            }
            if (direction.equals("east"))
            {
                west = source;
            }
            else if (this.randomRange(10) < depth)
            {
                west = new Room(this, "west", d);
            }
        }
        special = this.randomRange(100);
        if (special < 5)
        {
            action = new GrueRoomAction();
            special = 0;
        }
        else if (special < 15)
        {
            action = new TreasureRoomAction();
            special = 1;
        }
        else if (special < 23)
        {
            action = new FactorialRoomAction();
            special = 2;
        }
        else if (special < 31)
        {
            action = new BFRoomAction();
            special = 3;
        }
        else if (special < 40)
        {
            action = new JokeRoomAction();
            special = 4;
        }
        else if (special < 50)
        {
            action = new FeastRoomAction();
            special = 5;
        }
        else if (special < 62)
        {
            action = new CoinRoomAction();
            special = 6;
        }
        else if (special < 72)
        {
            action = new ExitRoomAction();
            special = 7;
        }
        else if (special < 85)
        {
            action = new HuntRoomAction();
            special = 8;
        }
        else
        {
            action = new EmptyRoomAction();
            special = this.randomRange(4) + 9;
        }
        description = this.generateDescription(special);
    }

    public int randomRange(int range){
        int num;
        JoosRandom rand;
        rand = new JoosRandom(1337);
        num = rand.nextInt()%range;
        if (num >= 0)
        {
            return num;
        }
        return -num;
    }

    public void getDescription()
    {
        io.println(description);
    }

    public Room getNorth()
    {
        return north;
    }

    public Room getSouth()
    {
        return south;
    }

    public Room getWest()
    {
        return west;
    }

    public Room getEast()
    {
        return east;
    }

    public RoomAction getRoomAction()
    {
        return action;
    }

    public void enterRoom()
    {
        io.println("==========================================================");
        this.getDescription();
        action.describe();
        io.println("There are exits:");
        if (this.getNorth() != null) {
            io.println(" -north");
        }
        if (this.getSouth() != null) {
            io.println(" -south");
        }
        if (this.getWest() != null) {
            io.println(" -west");
        }
        if (this.getEast() != null) {
            io.println(" -east");
        }
        io.println("");
    }

    public String generateDescription(int number)
    {
        if (number == 0)
        {
            return "It is pitch black. You are likely to be eaten by a grue.";
        }
        else if (number == 1)
        {
            return "You are in a large hall. Centered in this otherwise empty and silent room is an alabaster pedestal.";
        }
        else if (number == 2)
        {
            return "You are in a small room. On the east wall, there is a large rusty panel. At the top, two numbered dials spin rapidly, followed by an exclamation point. Below, there are 9 numbered dials spinning.";
        }
        else if (number == 3)
        {
            return "You are in a dusty padded room. On a simple desk in the middle of the room, a terminal displays '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.'.";
        }
        else if (number == 4)
        {
            return "You are in into a delapidated theater. The seats are empty and broken, the banners all ripped to shreds. Yet standing behind a splintered podium at the center of the stage, a lanky, bald man stands patiently.";
        }
        else if (number == 5)
        {
            return "You are in a large banquet hall. Spread before you on a table long enough to seat a hundred people is a feast of unimaginable bounty, but there is nobody here. As you walk along it, you see your favorite foods nestled in between delicious-looking foods that you cannot even name.";
        }
        else if (number == 6)
        {
            return "You are in a dark cave through which a small bubbling creek passes. There are a dozen skeletons, all resting alongside this stream. You search them for valuables.";
        }
        else if (number == 7)
        {
            return "You are in a hall with nothing of note other than a lone stone staircase rising up into the air before you. It does not appear to be supported by anything.";
        }
        else if (number == 8)
        {
            return "You are in a forest. You hear the leaves rustling in the wind.";
        }
        else if (number == 9)
        {
            return "You see before you a vast desert. High overhead, vultures are circling above.";
        }
        else if (number == 10)
        {
            return "You are in a small cottage. It looks like nobody's lived here for a long time, and a thick layer of dust covers everything.";
        }
        else if (number == 11)
        {
            return "You find yourself in a completely white room with no features other than the exits. You cannot tell whether the white ceiling is nearby or far away, and it's too far away to reach.";
        }
        else if (number == 12)
        {
            return "You are in a large underground cavern.";
        }
        else
        {
            return "You are in a non-descript room. How did you get here?";
        }
    }
}
