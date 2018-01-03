import joos.lib.*;

public class HuntRoomAction extends RoomAction{
    protected boolean taken;
    protected String target;

    public HuntRoomAction(){
        super();
        int n;
        n = this.rand(4);
        if (n == 0){
            target = "fierce ogre";
        }else if (n == 1){
            target = "rabbit";
        }else if (n == 2){
            target = "dark demon";
        }else if (n == 3){
            target = "puppy";
        }else{
            target = "wtf";
        }
        taken = false;
    }

    public void describe(){
        if (!taken)
            O.println("A wild " + target + " appears!");
        else
            O.println("The carcass of a " + target + " lies before you.");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("strike", 0) >= 0 ||
                inputString.indexOf("attack", 0) >= 0 ||
                inputString.indexOf("hunt", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ||
                inputString.indexOf("shoot", 0) >= 0 ||
                inputString.indexOf("hit", 0) >= 0 ||
                inputString.indexOf("ram", 0) >= 0 ||
                inputString.indexOf("charge", 0) >= 0 ||
                inputString.indexOf("punch", 0) >= 0 ||
                inputString.indexOf("fight", 0) >= 0 ||
                inputString.indexOf("kick", 0) >= 0 ||
                inputString.indexOf("grab", 0) >= 0 ||
                inputString.indexOf("swing", 0) >= 0 ||
                inputString.indexOf("hurt", 0) >= 0){
            if (taken){
                O.println("The " + target + " is already dead.");
                return 0;
            }else if (this.rand(100) > 60){
                O.println("Your attack succeeded!");
                O.println("You rip out the heart of your prey and takes a bite.");
                if (target.equals("puppy")){
                    O.println("You monster!");
                }else{
                    O.println("You feel energized.");
                }
                taken = true;
                return 8;
            }else if (this.rand(100) > 80){
                O.println("Your attack failed. But you managed to dodge the " + target + "'s attack and avoid taking damage.");
                return 0;
            }else{
                O.println("Your attack failed. The counter attack from the " + target + " left you wounded.");
                return 10;
            }
        }else if (inputString.indexOf("run", 0) >= 0 ||
                inputString.indexOf("escape", 0) >= 0 ||
                inputString.indexOf("leave", 0) >= 0){
            if (this.rand(100) > 90 && !taken){
                O.println("The " + target + " was startled by your indecision. It ran away.");
                taken = true;
            }
            O.println("Which direction?");
            return 0;
        }else{
            return this.performBaseAction(inputString);
        }
    }
}
