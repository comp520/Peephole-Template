
package joos.lib;

import java.util.*;

public class JoosRandom {

  Random myRandom;

  public JoosRandom() { myRandom = new Random(); }

  public JoosRandom(int seed) { myRandom = new Random((long) seed); }

  public int nextInt() { return (myRandom.nextInt()); }

  public synchronized void setSeed(int seed) { myRandom.setSeed((long) seed); }

}
  



