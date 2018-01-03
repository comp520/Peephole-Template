import joos.lib.*;

public class GrueRoomAction extends RoomAction{
    public GrueRoomAction(){
        super();
    }

    public int performAction(String inputString){
        if (inputString.indexOf("fight", 0) >= 0){
            O.println("You are ambushed.");
        }else if (inputString.indexOf("defend", 0) >= 0){
            O.println("You die from lack of sustenance.");
        }else if (inputString.indexOf("light", 0) >= 0){
            O.println("You have nothing with which to lighten up the room.");
        }else if (inputString.indexOf("run", 0) >= 0){
            O.println("You are too slow.");
        }
        O.print("You are eaten by a grue. ");
        return 1;
    }
}
