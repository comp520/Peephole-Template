package joos.lib;

import java.awt.*;

public class JoosDimension extends Dimension {
  private Dimension jd;

  public JoosDimension(Dimension d) 
   { super(); 
     jd = d; 
   }

  public int height() { return(jd.height); }

  public int width() { return(jd.width); }

  public void setHeight(int h) { jd.height = h; }

  public void setWidth(int w)  { jd.width = w; }

  public Dimension getDimension() { return(jd); }
}
