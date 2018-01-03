import java.util.*;
import joos.lib.*;

// Warning, this class exists only to make your eyes bleed. You can safely assume
// that these are sound lookup tables. In fact, I spent about an hour trying to
// figure out why the base64 decode was glitchy. Then I found that I had accidentally
// typed '28' twice down there while converting from hexadecimal. Many kitties were
// slaughetered that evening.
public class Conversion {
    
    protected Vector base64_key; 
    protected Vector base64_to10;
    
    public Conversion() { 
        super();

        base64_key = new Vector();
        /* Map base10 to base64 in constant time. */
	        base64_key.addElement("A"); base64_key.addElement("B"); base64_key.addElement("C"); base64_key.addElement("D"); base64_key.addElement("E"); base64_key.addElement("F"); base64_key.addElement("G"); base64_key.addElement("H"); base64_key.addElement("I"); base64_key.addElement("J"); base64_key.addElement("K"); base64_key.addElement("L"); base64_key.addElement("M"); base64_key.addElement("N");
    	    base64_key.addElement("O"); base64_key.addElement("P"); base64_key.addElement("Q"); base64_key.addElement("R"); base64_key.addElement("S"); base64_key.addElement("T"); base64_key.addElement("U"); base64_key.addElement("V"); base64_key.addElement("W"); base64_key.addElement("X"); base64_key.addElement("Y"); base64_key.addElement("Z"); base64_key.addElement("a"); base64_key.addElement("b");
    	    base64_key.addElement("c"); base64_key.addElement("d"); base64_key.addElement("e"); base64_key.addElement("f"); base64_key.addElement("g"); base64_key.addElement("h"); base64_key.addElement("i"); base64_key.addElement("j"); base64_key.addElement("k"); base64_key.addElement("l"); base64_key.addElement("m"); base64_key.addElement("n"); base64_key.addElement("o"); base64_key.addElement("p");
    	    base64_key.addElement("q"); base64_key.addElement("r"); base64_key.addElement("s"); base64_key.addElement("t"); base64_key.addElement("u"); base64_key.addElement("v"); base64_key.addElement("w"); base64_key.addElement("x"); base64_key.addElement("y"); base64_key.addElement("z"); base64_key.addElement("0"); base64_key.addElement("1"); base64_key.addElement("2"); base64_key.addElement("3");
    	    base64_key.addElement("4"); base64_key.addElement("5"); base64_key.addElement("6"); base64_key.addElement("7"); base64_key.addElement("8"); base64_key.addElement("9"); base64_key.addElement("+"); base64_key.addElement("/");

	    /* Map base64 to base10 in constant time */
        base64_to10 = new Vector();
    	    base64_to10.addElement("0");   base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0"); /*   0 - 9   */
    	    base64_to10.addElement("0");   base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0"); /*  10 - 19  */
    	    base64_to10.addElement("0");   base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0"); /*  20 - 29  */
    	    base64_to10.addElement("0");   base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0"); /*  30 - 39  */
    	    base64_to10.addElement("0");   base64_to10.addElement("0");  base64_to10.addElement("0"); base64_to10.addElement("62");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0"); base64_to10.addElement("63"); base64_to10.addElement("52"); base64_to10.addElement("53"); /*  40 - 49  */
    	    base64_to10.addElement("54"); base64_to10.addElement("55"); base64_to10.addElement("56"); base64_to10.addElement("57"); base64_to10.addElement("58"); base64_to10.addElement("59"); base64_to10.addElement("60"); base64_to10.addElement("61");  base64_to10.addElement("0");  base64_to10.addElement("0"); /*  50 - 59  */
    	    base64_to10.addElement("0");   base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("1");  base64_to10.addElement("2");  base64_to10.addElement("3");  base64_to10.addElement("4"); /*  60 - 69  */
    	    base64_to10.addElement("5");   base64_to10.addElement("6");  base64_to10.addElement("7");  base64_to10.addElement("8");  base64_to10.addElement("9"); base64_to10.addElement("10"); base64_to10.addElement("11"); base64_to10.addElement("12"); base64_to10.addElement("13"); base64_to10.addElement("14"); /*  70 - 79  */
    	    base64_to10.addElement("15"); base64_to10.addElement("16"); base64_to10.addElement("17"); base64_to10.addElement("18"); base64_to10.addElement("19"); base64_to10.addElement("20"); base64_to10.addElement("21"); base64_to10.addElement("22"); base64_to10.addElement("23"); base64_to10.addElement("24"); /*  80 - 89  */
    	    base64_to10.addElement("25");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0");  base64_to10.addElement("0"); base64_to10.addElement("26"); base64_to10.addElement("27"); base64_to10.addElement("28"); /*  90 - 99  */
    	    base64_to10.addElement("29"); base64_to10.addElement("30"); base64_to10.addElement("31"); base64_to10.addElement("32"); base64_to10.addElement("33"); base64_to10.addElement("34"); base64_to10.addElement("35"); base64_to10.addElement("36"); base64_to10.addElement("37"); base64_to10.addElement("38"); /* 100 - 109 */
    	    base64_to10.addElement("39"); base64_to10.addElement("40"); base64_to10.addElement("41"); base64_to10.addElement("42"); base64_to10.addElement("43"); base64_to10.addElement("44"); base64_to10.addElement("45"); base64_to10.addElement("46"); base64_to10.addElement("47"); base64_to10.addElement("48"); /* 110 - 119 */
    	    base64_to10.addElement("49"); base64_to10.addElement("50"); base64_to10.addElement("51"); /* 0 - 122 ASCII */ // F*** YEAH REGEXP
    }

    public char get64(int p) {
        String s;
        s = (String)base64_key.elementAt(p); // SMH
        return s.charAt(0);
    }

    public char get10(int p) {
        Integer intval;
        intval = new Integer((String)base64_to10.elementAt(p));
        return (char)intval.intValue();
    }
}
