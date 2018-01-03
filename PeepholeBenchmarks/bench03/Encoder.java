import java.util.*;
import joos.lib.*;
import lib.*;

public class Encoder {

    protected Conversion con;
    protected JoosBitwise uti;

    public Encoder() { 
        super(); 
        con = new Conversion();
        uti = new JoosBitwise();
    }

    public String base64_encode(String buffer)
    {
        int key;
        int size;
        int rest,i;
        String out;
        
        out = "";
        key = 0; 
        size = buffer.length();
        rest = size % 3;
        
        i = 0;
        while( i < size )
        {
            /* Reset the key. */
            key = 0; 
            if( size - i == rest )
            {
                /* Compute the last character. */
                if ( rest == 2 )
                    key = uti.or(key, uti.shl(buffer.charAt(i+1),8)); 
                key = uti.or(key, (uti.shl(buffer.charAt(i), 16)));
                    /* Put characters in buffer */
                out = out+con.get64( uti.and(uti.shr(key,18), 63) );
                out = out+con.get64( uti.and(uti.shr(key,12), 63) );

                if ( rest == 2 )
                    out = out+con.get64( uti.and(uti.shr(key,6), 63) );
                else
                    out = out + '=';
                out = out + '=';
                /* Move forward. */
                i = i+rest;
            }
            else
            {
                /* Load 3 unencoded bytes. */
                key = uti.or(key,uti.shl(buffer.charAt(i),16));
                i=i+1;
                key = uti.or(key,uti.shl(buffer.charAt(i),8));
                i=i+1;
                key = uti.or(key,buffer.charAt(i));
                i=i+1;
                /* Put characters in buffer. */
                out = out+con.get64( uti.and(uti.shr(key,18), 63) );
                out = out+con.get64( uti.and(uti.shr(key,12), 63) );
                out = out+con.get64( uti.and(uti.shr(key,6), 63) );
                out = out+con.get64( uti.and(key, 63) );
            }
        }
        
        /* Return string. */
        return out;
    }
}
