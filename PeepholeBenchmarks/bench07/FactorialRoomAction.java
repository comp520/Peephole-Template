import joos.lib.*;

public class FactorialRoomAction extends RoomAction{
    public FactorialRoomAction(){
        super();
    }

    public void describe(){
        O.println("There is a red button.");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("use", 0) >= 0 || 
                inputString.indexOf("operate", 0) >= 0 ||
                inputString.indexOf("press", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ||
                inputString.indexOf("factorial", 0) >= 0 ||
                inputString.indexOf("push", 0) >= 0){
            JoosRandom rand;
            int num;

            rand = new JoosRandom(1337);
            num = rand.nextInt() % 13;
            if (num < 0)
                num = -num;

            O.println("The dials come to a stop. Showing:");
            O.println(num + "!\n---");
            O.println("" + this.f(num));
            O.println("The dials resume spinning.");
            return 0; 
        }else{
            return this.performBaseAction(inputString);
        }
    }

    public int f(int n){
        if (n == 0 || n == 1)
            return 1;
        else
            return n * this.f(n - 1);
    }
}
