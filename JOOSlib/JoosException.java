package joos.lib;

public class JoosException extends RuntimeException {

  JoosException(String emessage)
   { super("<JOOS Exception ... " + emessage + ">");
   }
}
