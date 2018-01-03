import joos.lib.*;

public class BFRoomAction extends RoomAction{
    public BFRoomAction(){
        super();
    }

    public void describe(){
        O.println("There is a red button.");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("use", 0) >= 0 || 
                inputString.indexOf("operate", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ||
                inputString.indexOf("press", 0) >= 0 ||
                inputString.indexOf("push", 0) >= 0){
            O.println("Hello World");
            return 0; 
        }else{
            return this.performBaseAction(inputString);
        }
    }
}
