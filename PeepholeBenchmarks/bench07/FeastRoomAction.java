import joos.lib.*;

public class FeastRoomAction extends RoomAction{
    public FeastRoomAction(){
        super();
    }

    public void describe(){
        O.println("");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("use", 0) >= 0 || 
                inputString.indexOf("eat", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ||
                inputString.indexOf("consume", 0) >= 0){
            JoosRandom rand;
            int n;

            rand = new JoosRandom(1337);
            n = rand.nextInt() % 100;
            if (n < 0)
                n = -n;

            if (n < 40){
                O.println("The food leaves a bitter aftertaste. You feel weakened.");
                return 10;
            }else{
                O.println("The food was delicious! You feel energized.");
                return 7;
            }
        }else if (inputString.indexOf("flip", 0) >= 0){
            O.println("You hurt yourself in the process. A new table appears. ");
            return 9;
        }else{
            return this.performBaseAction(inputString);
        }
    }
}
