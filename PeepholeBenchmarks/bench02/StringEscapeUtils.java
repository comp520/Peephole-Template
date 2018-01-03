public class StringEscapeUtils
{
    public StringEscapeUtils()
    {
        super();
    }

    // Escape a string with part of LOLCODE's colon escape rules;
    public String escape(String str)
    {
        String escaped;

        escaped = this.replace(str, "::", ":");
        escaped = this.replace(escaped, ":)", "\n");
        escaped = this.replace(escaped, ":o", "\0007");
        escaped = this.replace(escaped, ":>", "\t");

        return escaped;
    }

    public String replace(String str, String from, String to)
    {
        int start;
        int pos;
        String head;
        String rest;

        pos = str.indexOf(from, 0);

        // Found
        if(pos >= 0)
        {
            head = str.substring(0, pos);
            rest = str.substring(pos + from.length(), str.length());

            return head + to + this.replace(rest, from, to);
        }

        return str;
    }
}
