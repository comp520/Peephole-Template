package joos.lib;

import java.awt.*;

public class JoosEvent extends Object {

  private Event je;

  public JoosEvent(Event e)
    { super();
      je=e; 
    }

  public Object arg()      { return(je.arg);        }
  public int clickCount()  { return(je.clickCount); }
  public Event evt()       { return(je.evt);        }
  public int id()          { return(je.id);         }
  public int key()         { return(je.key);        }
  public int modifiers()   { return(je.modifiers);  }
  public Object target()   { return(je.target);     }
  public int when()        { return((int) je.when); }
  public int x()           { return(je.x);          }
  public int y()           { return(je.y);          }

  public void setArg(Object a)       { je.arg = a;        }
  public void setClickCount(int c)   { je.clickCount = c; }
  public void setEvent(Event e)      { je.evt = e;        }
  public void setId(int i)           { je.id = i;         } 
  public void setKey(int k)          { je.key = k;        }
  public void setModifiers(int m)    { je.modifiers = m;  }
  public void setTarget(Object t)    { je.target = t;     }
  public void setWhen(int w)         { je.when = w;       }
  public void setX(int xx)           { je.x = xx;         }
  public void setY(int yy)           { je.y = yy;         }

  public Event getEvent() { return (je); } 
}
