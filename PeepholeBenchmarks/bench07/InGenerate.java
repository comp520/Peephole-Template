import joos.lib.*;

public class InGenerate{
    protected JoosRandom rand;

    public InGenerate(){
        super();
        rand = new JoosRandom(1337);
    }

    public static void main (String[] args){
        int i;
        int n;
        InGenerate g;
        JoosIO O;

        g = new InGenerate();
        O = new JoosIO();
        i = 0;
        n = 0;

        O.println("Dave");

        while (i < 500){
            n = g.randRange(4);
            if (n == 0){
                O.println("go north");
            }else if (n == 1){
                O.println("go south");
            }else if (n == 2){
                O.println("go east");
            }else if (n == 3){
                O.println("go west");
            }
            if (g.randRange(100) > 30){
                O.println("interact");
            }
            if (g.randRange(100) > 70){
                O.println("show hp");
            }
            if (g.randRange(100) > 70){
                O.println("show treasure");
            }
            if (g.randRange(100) > 70){
                O.println("show coin");
            }
            i = i + 1;
        }
    }

    public int randRange(int max){
        int n;
        n = rand.nextInt();
        if (n < 0)
            n = -n;
        return n % max;
    }
}
