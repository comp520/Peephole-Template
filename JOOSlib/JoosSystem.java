package joos.lib;

public final class JoosSystem {
  public int currentTimeMillis()
    { long l;
      l = System.currentTimeMillis();
      // if ((l > Integer.MAX_VALUE) || (l < Integer.MIN_VALUE))
      //  throw new JoosException("currentTimeMillis returns more than int");
      // else
        return((int) l);
    }

  public void gc() {
    System.gc();
  }

  public void runFinalization() {
    System.runFinalization();
  }

  public void exit(int value) {
    System.exit(value);
  }
 
}
  



