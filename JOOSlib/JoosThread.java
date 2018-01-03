package joos.lib;

public class JoosThread  {
  // my copy of a real JAVA thread
  protected Thread myThread;

  // constructor
  public JoosThread(Thread t) { super(); myThread = t; }

  // get at constants
  public int MAX_PRIORITY()   { return(Thread.MAX_PRIORITY);}
  public int MIN_PRIORITY()   { return(Thread.MIN_PRIORITY);}
  public int NORM_PRIORITY()  { return(Thread.NORM_PRIORITY);}

  // get at static methods
  public int activeCount()      { return(Thread.activeCount()); }
  public Thread currentThread() { return(Thread.currentThread()); }
  public void dumpStack()       { Thread.dumpStack();  }
  public void yield()           { Thread.yield(); }     

  public boolean sleep(int millis)  
   // returns true if interrupted, false otherwise
    { try
        { Thread.sleep((long) millis); 
          return(false);
        }
      catch (InterruptedException e)
        { return(true);
        }
    }

  // make a join that takes an int argument and returns bool
  public final synchronized boolean join(int millis) 
    //  returns true if interrupted, false otherwise
    { try
        { myThread.join((long) millis); 
          return(false);
        }
      catch (InterruptedException e)
        { return(true);
        }
    }
}

