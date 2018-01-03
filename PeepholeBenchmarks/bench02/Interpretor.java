import joos.lib.*;

public class Interpretor
{
    protected String state;
    protected JoosIO f;
    protected boolean ioImported;
    protected StringEscapeUtils escape;

    public Interpretor()
    {
        super();

        state = "init";
        f = new JoosIO();
        ioImported = false;
        escape = new StringEscapeUtils();
    }

    public void interpret(String cmd)
    {
        if(state.equals("init"))
        {
            this.init(cmd);
        } 
        else if(state.equals("running"))
        {
            this.run(cmd);
        }
    }

    public void init(String cmd)
    {
        if(!cmd.equals("HAI"))
        {
            this.crashed("Program must start with 'HAI'");
        }
        else
        {
            state = "running";
        }
    }


    //// Whether stdio lib has been imported.
    public void crashed(String errorInfo)
    {
        this.exit();
        f.println(errorInfo);
    }

    public void exit()
    {
        state = "exit";
    }

    public void run(String cmd)
    {
        if(cmd.startsWith("CAN", 0))
        {
            this.openMod(cmd);
        }
        else if(cmd.startsWith("VISIBLE", 0))
        {
            this.visible(cmd);
        }
        else if(cmd.equals("KTHXBYE"))
        {
            this.exit();
        }
        else
        {
            this.crashed("'" + cmd + "' can not be recognized");
        }
    }

    public void visible(String cmd)
    {
        String unEscaped;
        if(!ioImported) {
            this.crashed("Can not execute VISIBLE with out stdio");
        }

        unEscaped = cmd.substring(9, cmd.length() - 1);
        f.println(escape.escape(unEscaped));
    }

    public void openMod(String cmd)
    {
        if(!cmd.equals("CAN HAS STDIO?")) {
            this.crashed("Only module 'STDIO' is supported");
        }

        ioImported = true;
    }
}
