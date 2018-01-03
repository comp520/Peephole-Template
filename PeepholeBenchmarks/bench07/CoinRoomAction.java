import joos.lib.*;

public class CoinRoomAction extends RoomAction{
    protected boolean taken;

    public CoinRoomAction(){
        super();
        taken = false;
    }

    public void describe(){
        if (!taken)
            O.println("Ooooooh! Shiny!");
        else
            O.println("");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("pick up", 0) >= 0 ||
                inputString.indexOf("take", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ||
                inputString.indexOf("get ", 0) >= 0){
            if (taken){
                O.print("You have already picked up the coin.");
                return 0;
            }else{
                O.print("You picked up a gold coin! Your coin count: ");
                taken = true;
                return 5; 
            }
        }else if (inputString.indexOf("examin", 0) >= 0 ||
                inputString.indexOf("look", 0) >= 0 ||
                inputString.indexOf("inspect", 0) >= 0){
            O.println("It's a coin!");
            return 0;
        }else if(inputString.indexOf("drink", 0) >= 0){
            O.println("You feel flesh being torn from your body. "); 
            return 1;
        }else{
            return this.performBaseAction(inputString);
        }
    }
}
