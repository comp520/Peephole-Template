import joos.lib.*;

public class EmptyRoomAction extends RoomAction{
    public EmptyRoomAction(){
        super();
    }
    
    public void describe(){
        O.println("There doesn't seem to be anything to do here.");
    }

    public int performAction(String inputString){
        return this.performBaseAction(inputString);
    }
}
