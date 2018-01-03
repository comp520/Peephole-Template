/*
 * JOOS is Copyright (C) 1997 Laurie Hendren & Michael I. Schwartzbach
 *
 * Reproduction of all or part of this software is permitted for
 * educational or research use on condition that this copyright notice is
 * included in any copy. This software comes with no warranty of any
 * kind. In no event will the authors be liable for any damages resulting from
 * use of this software.
 *
 * email: hendren@cs.mcgill.ca, mis@brics.dk
 */


/* Modification history
 *
 * 2000/10/04 - DB : support for slash-star comments added
 * 2000/10/06 - DB : debug a comment regular expression
 *
 */



%{
#include "y.tab.h"
#include <string.h>
#include "tree.h"

extern int lineno;
%}

/* Declaring comment start condition - Added by David */
%x comment

%%
[ \t]+                   /* ignore */;
\n                       lineno++;
\/\/[^\n]*\n             lineno++;


                         /* Support for slash-star comments. */
                         /* Added by David 2000-10-4 */
"/*"                     BEGIN(comment);
<comment>[^*\n]*         /* eat everything not a * and not a \n */
<comment>"*"+[^*/\n]*    /* eat every * not followed by a / */
<comment>\n              lineno++;
<comment>"*"+"/"         BEGIN(INITIAL);   /* end of comment reached */



abstract                 return tABSTRACT;
boolean                  return tBOOLEAN;
break                    return tBREAK;
byte                     return tBYTE;
case                     return tCASE;
catch                    return tCATCH;
char                     return tCHAR;
class                    return tCLASS;
const                    return tCONST;
continue                 return tCONTINUE;
default                  return tDEFAULT;
do                       return tDO;
double                   return tDOUBLE;
else                     return tELSE;
extends                  return tEXTENDS;
extern                   return tEXTERN;
final                    return tFINAL;
finally                  return tFINALLY;
float                    return tFLOAT;
for                      return tFOR;
goto                     return tGOTO;
if                       return tIF;
implements               return tIMPLEMENTS;
import                   return tIMPORT;
in                       return tIN;
instanceof               return tINSTANCEOF;
int                      return tINT;
interface                return tINTERFACE;
long                     return tLONG;
main                     return tMAIN;
native                   return tNATIVE;
new                      return tNEW;
null                     return tNULL;
package                  return tPACKAGE;
private                  return tPRIVATE;
protected                return tPROTECTED;
public                   return tPUBLIC;
return                   return tRETURN;
short                    return tSHORT;
static                   return tSTATIC;
super                    return tSUPER;
switch                   return tSWITCH;
synchronized             return tSYNCHRONIZED;
this                     return tTHIS;
throw                    return tTHROW;
throws                   return tTHROWS;
transient                return tTRANSIENT;
try                      return tTRY;
void                     return tVOID;
volatile                 return tVOLATILE;
while                    return tWHILE;
"="                      return '=';
">"                      return '>';
"<"                      return '<';
"!"                      return '!';
"=="                     return tEQ;
"<="                     return tLEQ;
">="                     return tGEQ;
"!="                     return tNEQ;
"&&"                     return tAND;
"||"                     return tOR;
"+"                      return '+';
"-"                      return '-';
"*"                      return '*';
"/"                      return '/';
"%"                      return '%';
"{"                      return '{';
"}"                      return '}';
";"                      return ';';
"("                      return '(';
")"                      return ')';
"["                      return '[';
"]"                      return ']';
","                      return ',';
"."                      return '.';
"++"                     return tINC;
'\\b'                  { yylval.charconst = '\b';
                         return tCHARCONST; }
'\\t'                  { yylval.charconst = '\t';
                         return tCHARCONST; }
'\\n'                  { yylval.charconst = '\n';
                         return tCHARCONST; }
'\\f'                  { yylval.charconst = '\f';
                         return tCHARCONST; }
'\\r'                  { yylval.charconst = '\r';
                         return tCHARCONST; }
'\\\"'                 { yylval.charconst = '\"';
                         return tCHARCONST; }
'\\''                  { yylval.charconst = '\'';
                         return tCHARCONST; }
'\\\\'                 { yylval.charconst = '\\';
                         return tCHARCONST; }
'\\[0-7][0-7][0-7]'    { yylval.charconst = 64*yytext[1]+8*yytext[2]+yytext[3]-73*'0';
                         return tCHARCONST; }
'''                      return tERROR;
'\\'                     return tERROR;
'.'                    { yylval.charconst = yytext[1];
                         return tCHARCONST; }
0|([1-9][0-9]*)        { yylval.intconst = atoi(yytext);
                         return tINTCONST; }
true                   { yylval.boolconst = 1;
                         return tBOOLCONST; }
false                  { yylval.boolconst = 0;
                         return tBOOLCONST; }
\"([^\"])*\"           { yylval.stringconst = (char*)malloc(strlen(yytext)-1);
                         yytext[strlen(yytext)-1] = '\0';
                         sprintf(yylval.stringconst,"%s",yytext+1);
                         return tSTRINGCONST; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                         sprintf(yylval.stringconst,"%s",yytext); 
                         return tIDENTIFIER; }
"import "([a-zA-Z_][a-zA-Z0-9_]*".")*("*"|[a-zA-Z_][a-zA-Z0-9_]*); return tPATH;
.                        return tERROR;
%%







