import joos.lib.*;

public class TreasureRoomAction extends RoomAction{
    protected boolean taken;
    public TreasureRoomAction(){
        super();
        taken = false;
    }

    public void describe(){
        if (!taken)
            O.println("There is a treasure box at the center of the room.");
        else
            O.println("The treasure box is empty.");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("pick up", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ||
                inputString.indexOf("take", 0) >= 0 ||
                inputString.indexOf("open", 0) >= 0 ||
                inputString.indexOf("get ", 0) >= 0){
            if (taken){
                O.println("The treasure box is empty.");
                return 0;
            }else{
                O.print("You open the treasure box and finds a treasure! Your treasure count: ");
                taken = true;
                return 3; 
            }
        }else{
            return this.performBaseAction(inputString);
        }
    }
}
