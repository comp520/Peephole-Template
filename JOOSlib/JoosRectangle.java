package joos.lib;

import java.awt.*;

public class JoosRectangle extends Rectangle {

  public JoosRectangle(int x, int y, int w, int h) 
     { super(x,y,w,h); }

  // getting the values from fields
  public int x()        { return (x); }
  public int y()        { return (y); }
  public int width()    { return (width); }
  public int height()   { return (height); }

  // setting the fields
  public void setX(int lx) { x = lx; };
  public void setY(int ly) { y = ly; };
  public void setWidth(int w)  { width = w; };
  public void setHeight(int h) { height = h; };
}
