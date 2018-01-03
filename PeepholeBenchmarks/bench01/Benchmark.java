import joos.lib.*;

public class Benchmark {
  public Benchmark() { super() ;}

  public static void main (String[] args){
    JoosIO jio ;
    String resolver ;
    SudokuSolver ss ;
    jio = new JoosIO() ;

    //resolver = jio.readLine() ;
    // Class is not available in Joos .....
    //Class c = Class.forName(resolver) ;
    //SudokuSolver ss = (SudokuSolver)c.newInstance() ;

    resolver = jio.readLine() ;

    // and no switch either.
    if (resolver == "backtrack" ) {
      ss = new BacktrackSolver() ;
    } else if ( resolver == "bruteforce") {
      ss = new BacktrackSolver() ;
    } else {
      ss = new BacktrackSolver() ;
    }

    ss.parse(jio) ;
    ss.solve();
    ss.print(jio) ;
  }
}
