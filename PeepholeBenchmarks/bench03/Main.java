import java.util.*;
import joos.lib.*;
import lib.*;

public class Main {

    public Main() { 
        super();        
    }

    public static void main(String[] args) {
        Encoder encoder;
        Decoder decoder;
        JoosIO io;
        String str,encoded,decoded;	

        encoder = new Encoder();
        decoder = new Decoder();
        io = new JoosIO();

        str = io.readLine();
        while (str != null) {
            decoded = decoder.base64_decode(str.trim());
            io.println(decoded);
            str = io.readLine();
        }
    }
}

