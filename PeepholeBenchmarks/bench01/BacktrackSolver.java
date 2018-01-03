import joos.lib.*;
import java.util.*;  

public class BacktrackSolver extends SudokuSolver {

    public BacktrackSolver() {
	super() ;
    }

    public int getVal(int row, int col) {
	Object o ;
	Object oo ;
	Vector v ;
	Integer val ;
	int res ;
	
	o = grid.elementAt(row) ;
	v = (Vector)o ;
	oo = v.elementAt(col) ; 
	val = (Integer)oo ;
	
	return val.intValue() ;
    }


    public void setVal(int row, int col, int val) {
	Object o ;
	Object oo ;
	Object ooo ;
	Vector v ;
	int res ;
	
	o = grid.elementAt(row) ;
	v = (Vector)o ;
	ooo = new Integer(val) ;
	v.setElementAt(ooo,col) ; 
    }
    
    public boolean checkRow( int row, int num )
    {
	int col ;
	
	for (col = 0; col < 9; col++ ) {
	    if ( this.getVal(row,col) == num ) {
		return false ;
	    }
	}
	return true ;
    }

    public boolean checkCol( int col, int num )
    {
	int row ;
	
	for( row = 0; row < 9; row++ ) {
	    if( this.getVal(row,col) == num )
		return false ;
	}
	return true ;
    }

    public boolean checkBox( int row, int col, int num )
    {
	int r ;
	int c ;
	
	row = (row / 3) * 3 ;
	col = (col / 3) * 3 ;

	for(r = 0; r < 3; r++ ) {
	    for(c = 0; c < 3; c++ ) {
		if ( this.getVal(row+r, col+c) == num ) {
		    return false ;
		}
	    }
	}
	return true ;
    }

    
    public boolean checkFinish() {
	int i ;
	int j ;

	for (i = 0 ; i < 9 ; i++ ) {
	    for (j = 0 ; j < 9 ; j++) {
		if ( this.getVal(i,j) == 0 ) {
		    return false ;
		}
	    }
	}

	return true ;

    }
    
    public void solveCell( int row, int col )
    {
	int num ;
	
	if (this.checkFinish()) {
	    return ;
	}
	
	// If the cell is not empty, continue with the next cell
	if( this.getVal(row,col) != 0 )
	    this.next( row, col ) ;
	else
	    {
		// Find a valid number for the empty cell
		for( num = 1; num < 10; num++ )
		    {
			if( this.checkRow(row,num) && this.checkCol(col,num) && this.checkBox(row,col,num) )
			    {
				if (!this.checkFinish()) {
				    this.setVal(row,col,num) ;
				}
				// Delegate work on the next cell to a recursive call
				this.next( row, col ) ;
			    }
		    }

		// No valid number was found, clean up and return to caller
		if (!this.checkFinish()) {
		    this.setVal(row,col,0) ;
		}
	    }
    }

    public void next( int row, int col )
    {
	if( col < 8 )
	    this.solveCell( row, col + 1 ) ;
	else
	    this.solveCell( row + 1, 0 ) ;
    }

    public void solve() {
	this.solveCell(0,0) ;
    }


}
