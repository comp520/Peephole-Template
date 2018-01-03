package joos.lib;

import java.awt.*;

public class JoosMediaTracker extends Object {
  protected MediaTracker myTracker;
  public JoosMediaTracker (MediaTracker m) { myTracker = m; }

  // returns true if interrupted
  public boolean waitForAll() 
    { try
        { myTracker.waitForAll();
          return(false);
        }
      catch (InterruptedException e)
        { return(true);
        }
     }

  public boolean waitForID(int id)
    { try
        { myTracker.waitForID(id);
          return(false);
        }
      catch (InterruptedException e)
        { return(true);
        }
     }

  public MediaTracker getMediaTracker() { return(myTracker); }
}
