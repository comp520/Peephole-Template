package joos.lib;

import java.awt.*;

public class JoosContainer extends Object {

  private Container jc;

  public JoosContainer(Container c)
    { super();
      jc=c; 
    }

  public Component addString(String name, Component comp)
    { return(jc.add(name,comp)); }
  
  public Component addPosition(Component comp, int pos)
    { return(jc.add(comp,pos)); }

}
