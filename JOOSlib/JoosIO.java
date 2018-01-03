package joos.lib;

public class JoosIO {
  public JoosIO() {};

  public void print(String str)
  {  System.out.print(str);  System.out.flush();
  }

  public void println(String str)
  {  System.out.println(str); System.out.flush();
  }

  public void flush()
  {  System.out.flush();
  }

  public boolean readBoolean() 
  { try 
     { String s;

       s = (new java.io.DataInputStream(System.in)).readLine();
       return((new Boolean(s)).booleanValue());
     }
    catch (java.io.IOException e)
     { throw new JoosException("IO Error in readBoolean"); }
  }

  public int readInt() 
  { String s;

    try 
     { s = (new java.io.DataInputStream(System.in)).readLine(); }
    catch (java.io.IOException e)
     { throw new JoosException("IO Error in readInt"); }
    try
     { return((new Integer(s)).intValue()); }
    catch (NumberFormatException e)
     { throw new JoosException("Number format error in readInt"); } 
  }

  public String readLine() 
  { try 
     { return((new java.io.DataInputStream(System.in)).readLine()); }
    catch (java.io.IOException e)
     { throw new JoosException("IO Error in readLine"); }
  }

}
