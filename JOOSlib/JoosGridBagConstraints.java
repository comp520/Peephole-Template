package joos.lib;

import java.awt.*;

public class JoosGridBagConstraints extends Object {
  private GridBagConstraints myConstraints;

  public JoosGridBagConstraints(GridBagConstraints c) 
    { super();  
      myConstraints = c;
    }

  // getting the values from fields
  public int anchor()        { return (myConstraints.anchor); }
  public int fill()          { return (myConstraints.fill);   } 
  public int gridheight()    { return (myConstraints.gridheight); }
  public int gridwidth()     { return (myConstraints.gridwidth);  }
  public int gridx()         { return (myConstraints.gridx); }      
  public int gridy()         { return (myConstraints.gridy); }
  public Insets insets()     { return (myConstraints.insets); }
  public int ipadx()         { return (myConstraints.ipadx);  }
  public int ipady()         { return (myConstraints.ipady);  }

  // setting the fields
  public void setAnchor(int i)     { myConstraints.anchor = i; }
  public void setFill(int i)       { myConstraints.fill = i;   }
  public void setGridHeight(int i) { myConstraints.gridheight = i; }
  public void setGridWidth(int i)  { myConstraints.gridwidth = i;  }
  public void setGridX(int i)      { myConstraints.gridx = i; } 
  public void setGridY(int i)      { myConstraints.gridy = i; }
  public void setInsets(Insets i)  { myConstraints.insets = i; }
  public void setIpadX(int i)      { myConstraints.ipadx = i; }
  public void setIpadY(int i)      { myConstraints.ipady = i; }
  public void setWeightX(JoosFraction f)  
    { myConstraints. weightx = (double) f.top() / (double) f.bot(); }
  public void setWeightY(JoosFraction f)  
    { myConstraints. weighty = (double) f.top() / (double) f.bot(); }


  // getting back a GridBagConstraints
  public GridBagConstraints getConstraints() { return(myConstraints); }
}
