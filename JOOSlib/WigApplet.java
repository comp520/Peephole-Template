package joos.lib;

import java.util.*;
import java.applet.Applet;

public class WigApplet extends Applet {

  protected Vector returnPasswords;

  protected Vector returnValues;

  protected JoosURL url;

  protected String URLString;
 
  protected JoosIO f;

  public WigApplet() 
   { super(); 
     returnPasswords = new Vector(5,1);
     returnValues = new Vector(5,1);
     f = new JoosIO();
   }

  public boolean openURL()
   { URLString = this.getParameter("cgi-url");
     url = new JoosURL(null,URLString);
     if (url.openConnection())
       { f.println("Opened <" + URLString + "> successfully.");
         return(true);
       }
     else
       { f.println("Could not open " + URLString);
         f.println(url.getErrorLog());
         return(false);
       }
   }

  public void addResult(String name, String value)
   { // add the password for param 
     returnPasswords.addElement(this.getParameter(name));
     // add the value for param 
     returnValues.addElement(value);
   }

  public boolean returnResults()
  { int i;
    String nextPassword, nextValue;
    if (url.openOutputStream())
      { // number of results
        url.println(new Integer(returnPasswords.size()).toString());
        f.println(new Integer(returnPasswords.size()).toString());
        // for each result
        for (i=0; i<returnPasswords.size(); i++)
          { nextPassword = (String) returnPasswords.elementAt(i);
            nextValue = (String) returnValues.elementAt(i);
            // send password, first length then actual password 
            url.println(new Integer(nextPassword.length()).toString());
            f.println(new Integer(nextPassword.length()).toString());
            url.println(nextPassword);
            f.println(nextPassword);
            // send value, first length and then actual value
            url.println(new Integer(nextValue.length()).toString());
            f.println(new Integer(nextValue.length()).toString());
            url.println(nextValue);
            f.println(nextValue);
          }
        url.closeOutputStream();
      }
 
    // if the error log is null, then no errors occurred
    if (url.getErrorLog() != null)
      { f.println("***** Errors returning values from applet were: ");
        f.println(url.getErrorLog());
        return(false);
      }
    else
      return(true);
   }

  public void getResponse()
  { String inputLine;

    //  now try to open the input stream, get text back from cgi form
    if (url.openInputStream())
      { // input stream opened ok, now read each line and echo
        while((inputLine = url.readLine()) != null)
          f.println(inputLine);
        // close the input stream
        url.closeInputStream();
       }
    // if the error log is null, then no errors occurred
    if (url.getErrorLog() != null)
      { f.println("***** Errors in getResponse from form were: ");
        f.println(url.getErrorLog());
      }
   }
 
}
