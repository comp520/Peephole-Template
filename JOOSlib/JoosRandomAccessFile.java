package joos.lib;

import java.io.*;

public class JoosRandomAccessFile {
  // my copy of a Java RandomAcessFile
  protected RandomAccessFile myFile;

  // constructor
  public JoosRandomAccessFile (String name, String mode ) 
     { try { myFile = new RandomAccessFile(name,mode); }
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void close()
     { try { myFile.close(); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public int length ()
     { try { return ((int) myFile.length()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public int read ()
     { try { return(myFile.read()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public boolean readBoolean()
     { try { return(myFile.readBoolean()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public int readInt()
     { try { return(myFile.readInt()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public String readLine()
     { try { return(myFile.readLine()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public String readUTF ()
     { try { return(myFile.readUTF()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public int readUnsignedByte()
     { try { return(myFile.readUnsignedByte()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public int readUnsignedShort()
     { try { return(myFile.readUnsignedShort()); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void seek(int pos)
     { try { myFile.seek(pos); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public int skipBytes(int n)
     { try { return(myFile.skipBytes(n)); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void write(int b)
     { try { myFile.write(b); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void writeBoolean(boolean v)
     { try { myFile.writeBoolean(v); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void writeByte(int v)
     { try { myFile.writeByte(v); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void writeBytes(String s)
     { try { myFile.writeBytes(s); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void writeChar(int v)
     { try { myFile.writeChar(v); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void writeChars(String s)
     { try { myFile.writeChars(s); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }
  
  public void writeInt(int v)
     { try { myFile.writeInt(v); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void writeShort(int v)
     { try { myFile.writeShort(v); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

  public void writeUTF(String str)
     { try { myFile.writeUTF(str); } 
       catch (IOException e)
         { throw new JoosException("IOException: " + e); }
     }

}


