package joos.lib;

public class JoosObject extends Object {
  protected Object myObject;

  public JoosObject(Object o) { myObject = o; }
  
  // return true if interrupted, false otherwise 
  public final boolean wait(int timeout)
   {  try
        { myObject.wait((long) timeout);
          return(false);
        }
      catch (InterruptedException e)
        { return(true);
        }
   }
}
