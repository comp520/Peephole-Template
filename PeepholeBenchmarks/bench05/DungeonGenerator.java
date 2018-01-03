/*
   A really simple dungeon generator

   By Jodi & Kevin.
   McGill 2011.
*/

import joos.lib.*;

public class DungeonGenerator {

    public DungeonGenerator() {
        super();
    }


    public static void main(String[] args) {
        DungeonInfos infos;
        Dungeon dungeon;
        JoosIO io;

        infos = new DungeonInfos();
        infos.initializeFromStdIn();

        dungeon = new Dungeon(infos);
        io = new JoosIO();

        dungeon.draw();
    }
}
