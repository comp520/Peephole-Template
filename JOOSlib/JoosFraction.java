package joos.lib;

public class JoosFraction extends Object {
// used to hold fractions, since we do not have real numbers in Joos
  private int top;
  private int bot;

  public JoosFraction(int t, int b)
    { super();
      top = t;
      bot = b;
    }
  
  public int bot() { return bot; }
  public int top() { return top; }
  public void setBot(int b) { bot = b; }
  public void setTop(int t) { top = t; }
}
