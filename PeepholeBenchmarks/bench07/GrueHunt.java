import joos.lib.*;

public class GrueHunt
{

    public GrueHunt()
    {
        super();
    }

    public String testLoop(JoosIO io, boolean giveup)
    {
        String s;
        s = null;
        if (!giveup)
        {
            s = io.readLine();
        }
        return s;
    }


    public static void main(String[] args)
    {
        JoosIO io;
        int coins;
        int treasure;
        int hp;
        int effect;
        int depth;
        int escape;
        boolean giveup;
        String name;
        String line;
        String logo;
        Room place;
        int escapeChance;
        GrueHunt g;

        g = new GrueHunt();
        giveup = false;
        logo = "╔═╝┏━┓╻ ╻┏━╸ ║ ║╻ ╻┏┓╻╺┳╸\n║ ║┣┳┛┃ ┃┣╸  ╔═║┃ ┃┃┗┫ ┃ \n══╝╹┗╸┗━┛┗━╸ ╝ ╝┗━┛╹ ╹ ╹ ";
        escapeChance = 20;
        escape = 100;
        io = new JoosIO();
        depth = 11;
        place = new Room(null,"null",depth);
        coins = 0;
        treasure = 0;
        hp = 10;

        io.println("\n" + logo);
        io.println("\n");
        io.println("Welcome to GrueHunt! Please don't feed the grues.");
        io.println("What is your name?");
        name = io.readLine();
        if (name == null || name.equals(""))
        {
            name = "Dave";
        }
        place.enterRoom();
        while ((line = g.testLoop(io,giveup)) != null)
        {
            io.println("");
            if (line.indexOf("give up", 0) >= 0)
            {
                io.println("You have given up, "+name+".");
                io.println("You spend the rest of your days wandering this bizarre world. Better luck next time!");
                giveup = true;
            }
            else if (line.indexOf("north", 0) >= 0)
            {
                Room target;

                target = place.getNorth();
                if (target == null)
                {
                    io.println("There is no exit that way.");
                }
                else
                {
                    place = target;
                    io.println("You go north.");
                }
            }
            else if (line.indexOf("south", 0) >= 0)
            {
                Room target;
                target = place.getSouth();
                if (target == null)
                {
                    io.println("There is no exit that way.");
                }
                else
                {
                    place = target;
                    io.println("You go south.");
                }
            }
            else if (line.indexOf("west", 0) >= 0)
            {
                Room target;
                target = place.getWest();
                if (target == null)
                {
                    io.println("There is no exit that way.");
                }
                else
                {
                    place = target;
                    io.println("You go west.");
                }
            }
            else if (line.indexOf("east", 0) >= 0)
            {
                Room target;
                target = place.getEast();
                if (target == null)
                {
                    io.println("There is no exit that way.");
                }
                else
                {
                    place = target;
                    io.println("You go east.");
                }
            }
            else
            {
                effect = (place.getRoomAction()).performAction(line);
                if (effect == 0)
                {
                }
                else if (effect == 1)
                {
                    hp = 0;
                }
                else if (effect == 2)
                {
                    io.print(name+".\n");
                }
                else if (effect == 3)
                {
                    treasure = treasure + 1;
                    io.println("You have "+treasure+" treasure(s).");
                }
                else if (effect == 4)
                {
                    io.println("You have "+treasure+" treasure(s).");
                }
                else if (effect == 5)
                {
                    coins = coins + 1;
                    io.println("You have "+coins+" coin(s).");
                }
                else if (effect == 6)
                {
                    io.println("You have "+coins+" coin(s).");
                }
                else if (effect == 7)
                {
                    hp = hp + 1;
                }
                else if (effect == 8)
                {
                    hp = hp + 2;
                }
                else if (effect == 9)
                {
                    hp = hp - 1;
                }
                else if (effect == 10)
                {
                    hp = hp - 2;
                }
                else if (effect == 11)
                {
                    io.println("You have "+hp+" hit points remaining.");
                }
                else if (effect == 12)
                {
                    escape = place.randomRange(100);
                    if (escape < escapeChance)
                    {
                        io.println("You've escaped this bizarre world! You are now free.");
                    }
                    else
                    {
                        depth = depth - 1;
                        if (depth == 5)
                        {
                            depth = 11;
                        }
                        place = new Room(null,"null",depth);
                        io.println("You suddenly notice the new place you find yourself.");
                    }
                }
                if (hp > 15)
                {
                    hp = 15;
                }
                if (hp < 1)
                {
                    io.println("\n\n"+name+" died.");
                    hp = 0;
                    giveup = true;
                }
                if (escape < escapeChance)
                {
                    giveup = true;
                }
            }
            if (!giveup)
            {
                io.println("");
                place.enterRoom();
            }
        }
        io.println(name+" has accumulated "+treasure+" treasure(s) and "+coins+" coin(s).");
        io.println(name+" has "+hp+" hit points remaining.");
        io.println("Thank you for playing\n"+logo);
    }
}
