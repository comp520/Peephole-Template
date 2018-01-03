import joos.lib.*;                                                                                                                                                                  
import java.util.*;

public abstract class SudokuSolver {

    protected Vector grid ;
    
    public SudokuSolver() {
	super() ;
    }
    
    public void parse(JoosIO jio) {
	int i ;
	int j ;
	Object dont_have_generic ;
	Vector so_i_subcast ;
	int value ;
	Integer val ;
	grid = new Vector(9) ;
	for (i = 0 ; i < 9 ; i++) {
		grid.addElement(new Vector(9)) ;
		for (j = 0 ; j < 9; j++) {
			dont_have_generic = grid.elementAt(i) ;
			so_i_subcast = (Vector)dont_have_generic ;
			value = jio.readInt() ;
			val = new Integer(value) ;
			so_i_subcast.addElement(val);
		}
		
	}
    }

    public abstract void solve() ;

    public void print(JoosIO jio) {
	int i ;
	int j ;
	int ii ;
	int jj ;
	ii = 0 ;
	for (i = 0 ; i < 12 ; i++) {
	    jj = 0 ;
	    for (j = 0 ; j < 13; j++) {
		if (i == 0 || i == 4 || i == 8 ) {
		    jio.print("|") ;
		} else {
		    if (j == 0 || j == 4 || j == 8 || j == 12) {
			jio.print("|") ;
		    } else {
			Object val ;
			Integer inte ;
			Integer zero ;
			String s ;
			Object vtemp ;
			Vector vtemp2 ; 
			vtemp = grid.elementAt(ii) ;
			vtemp2 = (Vector)vtemp ;
			val = vtemp2.elementAt(jj) ;
			jj++ ;
			zero = new Integer(0) ;
			inte = (Integer) val ;
			if ( inte != zero) {
			    s = inte.toString() ;
			   jio.print(s) ;
			} else {
			    jio.print(" ") ;
			}
		    }
		}
	    }
	if (i != 0 && i != 4 && i != 8 ) {
	    ii++ ;
	}
	jio.print("\n");
	}
    }
}
    
