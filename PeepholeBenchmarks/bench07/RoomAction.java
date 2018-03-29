import joos.lib.*;

public abstract class RoomAction{
    protected JoosIO O;
    protected JoosRandom R;

    protected String targetString;

    public RoomAction(){
        super();
        O = new JoosIO();
        R = new JoosRandom(1337);
    }

    public void describe(){
        O.println("");
    }
    
    public abstract int performAction(String inputString);

    public int performBaseAction(String inputString){
        if (inputString.indexOf("fortune", 0) >= 0){
            //
            //O.print();
        }else if (inputString.indexOf("show hp", 0) >= 0){
            return 11;
        }else if (inputString.indexOf("show treasure", 0) >= 0){
            return 4;
        }else if (inputString.indexOf("show coin", 0) >= 0){
            return 6;
        }else if (inputString.indexOf("leave", 0) >= 0 ||
                inputString.indexOf("go", 0) >= 0 
                ){
            O.println("Which direction?");
        }else{
            O.print("I'm afraid I can't let you do that, ");
            return 2;
        }
        return 0;
    }

    public int rand(int max){
        int n;
        n = R.nextInt();
        if (n < 0)
            n = -n;
        return n % max;
    }
}
