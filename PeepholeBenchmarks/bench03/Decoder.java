import java.util.*;
import joos.lib.*;
import lib.*;

public class Decoder {

	protected Conversion con;
    protected JoosBitwise uti;

    public Decoder() { 
        super(); 
        con = new Conversion();
        uti = new JoosBitwise();
    }


	public String base64_decode(String buffer) {
		int key;
        int size;
		int i;
        int pad;
	    String out;
	    
	    out = "";
		key = 0;
        pad = 0;
        size = buffer.length();
        i = size - 1;
	   
	    /* Count padding. */
		while (buffer.charAt(i) == '=') { 
            pad = pad + 1;
            i = i - 1;
        }
	    i = 0;

	    while (i < size) { // Everything except the 4 last characters
            key = 0; // Reset key
            if ((size - 4 == i) && (pad > 0)) { // Handle padding
                if (pad == 2) {
                    key = uti.or(key,uti.shl(con.get10(buffer.charAt(i)), 18));
                    out = out + (char)(uti.and(uti.shr(key, 16), 255));
                } else if (pad == 1) {
                    key = uti.or(key, uti.shl(con.get10(buffer.charAt(i)), 18));
                    i = i + 1;
                    key = uti.or(key, uti.shl(con.get10(buffer.charAt(i)), 12));
                    i = i + 1;
                    key = uti.or(key, uti.shl(con.get10(buffer.charAt(i)), 6));

                    out = out + (char)(uti.and(uti.shr(key,16), 255));
                    out = out + (char)(uti.and(uti.shr(key,8), 255));
                }
                return out;
            } else {
    	        /* Load 4 */
                key = uti.or(key, uti.shl(con.get10(buffer.charAt(i)),18));
                i = i+1;
                key = uti.or(key, uti.shl(con.get10(buffer.charAt(i)),12));
                i = i+1;
    	        key = uti.or(key, uti.shl(con.get10(buffer.charAt(i)),6));
                i = i+1;
    	        key = uti.or(key, con.get10(buffer.charAt(i)));
                i = i+1;
    	        /* Decode 3 */
    	        out = out + (char)(uti.and(uti.shr(key,16), 255));
    	        out = out + (char)(uti.and(uti.shr(key,8), 255));
    	 	    out = out + (char)(uti.and(key, 255));
    	    }
        }
	    return out;
	}
}
