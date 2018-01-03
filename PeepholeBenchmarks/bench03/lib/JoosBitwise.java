package lib;

public class JoosBitwise {
    public JoosBitwise(){}

    public int shl(int num, int amt) {
        return num << amt;
    }

    public int shr(int num, int amt) {
        return num >> amt;
    }

    public int and(int a, int b)
    {
        return a & b;
    }

    public int or(int a, int b)
    {
        return a | b;
    }

}

