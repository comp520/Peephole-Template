import joos.lib.*;

public class Main 
{
    public Main()
    {
        super();
    }

    public static void main(String args[]) 
    {
        JoosIO f;
        Interpretor it;
        String s;

        f = new JoosIO();
        it = new Interpretor();

        s = f.readLine();

        while(s != null)
        {
            it.interpret(s);
            s = f.readLine();
        }
    }
}
