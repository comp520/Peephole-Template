package joos.lib;

public class JoosString {
  private String mystring;

  public JoosString(String value) 
    { mystring = value; };

  public boolean string2Bool() 
    { return((new Boolean(mystring)).booleanValue()); }

  public int string2Int()
    { try
        { return((new Integer(mystring)).intValue()); }
      catch (NumberFormatException e)
        { throw new JoosException("Number format error in string2Int");
        }
    }

  public String valueOf() 
    { return (mystring); }
}
