package joos.lib;

import java.io.*;
import java.net.*;

public class JoosURL extends Object {
 
  protected URL myURL;                  
  protected URLConnection myConnection;
  protected PrintStream myOutputStream;
  protected DataInputStream myInputStream;
  protected String myErrorLog;

  public JoosURL(URL context, String spec)
    { super();
      myErrorLog = null ;
      try 
        { myURL = new URL(context,spec); 
        }
      catch (MalformedURLException e)
        { addLog("JoosURL: " + e);
          myURL = null;
        }
      myConnection = null;
      myOutputStream = null;
      myInputStream = null;
    }

  public Object getContent()
   { Object rvalue;
     try 
       { rvalue = myURL.getContent(); 
         return(rvalue);
       }
     catch (java.io.IOException e)
       { addLog("getContent: " + e);
         return(null);
       }
   }
       
  public URL getURL ()
    { return(myURL);
    }

  public boolean openConnection()
    { if (myURL != null) 
        { try
            { myConnection = myURL.openConnection(); 
              return(true);
            }
          catch (java.io.IOException e)
            { addLog("openConnection: " + e);
              return(false);
            }
         }
       else
         { addLog("openConnection: URL is null");
           return(false);
         }
     }      

   public boolean openOutputStream()
     {  OutputStream outStream; 

        if (myConnection != null)
          { try
             {  // must set connection for output, it is input only by default 
                myConnection.setDoOutput(true);
                outStream = myConnection.getOutputStream();
             }
            catch (java.io.IOException e)
              { addLog("openOutputStream: " + e);
                return(false);
              }
            myOutputStream = new PrintStream(outStream); 
            return(true);
          }
        else
          { addLog("openOutputStream: myConnection is null, make sure you opened it");
            return(false);
          }
      }


   public boolean println(String s)
      { if (myOutputStream != null)
          { myOutputStream.println(s);
            return(true);
          }
        else
          { addLog("println: myOutputStream is null, make sure you opened it"); 
            return(false);
          }
       }


   public boolean print(String s)
      { if (myOutputStream != null)
          { myOutputStream.print(s);
            return(true);
          }
        else
          { addLog("print: myOutputStream is null, make sure you opened it");
            return(false);
          }
       }

   public boolean closeOutputStream()
     { if (myOutputStream != null)
         { myOutputStream.close();
           myOutputStream = null;
           return(true);
         }
       else
         { addLog("closeOutputStream: closing null stream");
           return(false);
         }
      }


   public boolean openInputStream()
     {  if (myConnection != null)
           try
             { myInputStream = 
                  new DataInputStream(myConnection.getInputStream());
               return(true);
             }
           catch (java.io.IOException e)
             { addLog("openInputStream: " + e);
               return(false);
             }
         else
           { addLog("openInputStream:  myConnection null, make sure you opened it");
             return(false);
           }
      }

   public String readLine()
      { if (myInputStream != null)
          try
            { return(myInputStream.readLine());
            }
          catch (java.io.IOException e)
            { addLog("readLine: " + e);
              return(null);
            } 
        else
          { addLog("readLine: trying to real from null input stream");
            return(null);
          }
       }

   public boolean closeInputStream()
     { if (myInputStream != null)
         try
           { myInputStream.close();
             myInputStream = null;
             return(true);
           }
         catch (java.io.IOException e)
           { addLog("closeInputStream: " + e);
             return(false);
           }
       else
         { addLog("closeInputStream: closing null stream");
           return(false);
         } 
     }

    private void addLog(String s)
      {  if (myErrorLog == null)
           myErrorLog = "---> " + s;
         else
           myErrorLog = myErrorLog + "\n" + "---> " + s;
      }

    public String getErrorLog()
      { return(myErrorLog);
      }
}
