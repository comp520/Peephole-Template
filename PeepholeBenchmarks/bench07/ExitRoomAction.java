import joos.lib.*;

public class ExitRoomAction extends RoomAction{
    public ExitRoomAction(){
        super();
    }

    public void describe(){
        O.println("You see light shining from the top.");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("up", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ||
                inputString.indexOf("use", 0) >= 0){
            O.println("A trapdoor closes behind you. ");
            return 12;
        }else{
            return this.performBaseAction(inputString);
        }
    }
}
