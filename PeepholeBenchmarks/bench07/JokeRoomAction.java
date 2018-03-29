import joos.lib.*;

public class JokeRoomAction extends RoomAction{
    public JokeRoomAction(){
        super();
    }

    public void describe(){
        O.println("The old man seems talkative.");
    }

    public int performAction(String inputString){
        if (inputString.indexOf("listen", 0) >= 0 ||
                inputString.indexOf("interact", 0) >= 0 ){
            O.println("The old man speaks: ");
            this.printJoke();
            return 0;
        }else if (inputString.indexOf("talk", 0) >= 0 ||
                inputString.indexOf("speak", 0) >= 0 ||
                inputString.indexOf("hello", 0) >= 0){
            O.println("The old man ignores you and speaks:");
            this.printJoke();
            return 0;
        }else if (inputString.indexOf("ignore", 0) >= 0){
            O.println("The old man hits you with a fish. You feel weakened.");
            return 9;
        }else{
            return this.performBaseAction(inputString);
        }
    }

    public void printJoke(){
        JoosRandom rand;
        int n;

        rand = new JoosRandom(1337);
        n = rand.nextInt() % 10;
        if (n < 0)
            n = -n;

        if (n == 0){
            O.println("Two cannibals are eating a clown, when one asks the other 'does this taste funny to you?'");
        }else if (n == 1){
            O.println("Two peanuts were walking down the street, and one was assaulted.");
        }else if (n == 2){
            O.println("A sausage is sitting in a frying pan. Another sausage gets dropped in, and says 'holy crap, it's hot in here!' To which the first sausage replies 'holy crap, a talking sausage!'");
        }else if (n == 3){
            O.println("Have you heard about that new movie Constipation?\n\nIt hasn't come out yet.");
        }else if (n == 4){
            O.println("What's a foot long and slippery?\n\nA slipper!");
        }else if (n == 5){
            O.println("If H2O is on the inside of a fire hydrant, what's on the outside? \n\nK9P");
        }else if (n == 6){
            O.println("Two silk worms were in a race.\n\nIt ended in a tie.");
        }else if (n == 7){
            O.println("Werner Heisenberg is driving down the highway. Cop stops him and says, 'Sir, do you know how fast you were going?' Heisenberg says, 'No, but I know exactly where I am!'");
        }else if (n == 8){
            O.println("What's the difference between roast beef and pea soup?\n\nAnyone can roast beef.");
        }else if (n == 9){
            O.println("What do you get when you cross an elephant with a banana?\n\nElephant banana sine theta.");
        }else if (n == 10){
            O.println("What did the girl fungus say to the boy fungus?\n\nYou're a real fun guy.");
        }
    }
}
