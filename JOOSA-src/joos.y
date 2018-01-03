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

%{
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

extern CLASSFILE *theclassfile;
 
%}

%start classfile

%union {
   struct CLASSFILE *classfile;
   struct CLASS *class;
   struct FIELD *field;
   struct TYPE *type;
   struct ID *id;
   struct CONSTRUCTOR *constructor;
   struct METHOD *method;
   struct FORMAL *formal;
   struct STATEMENT *statement;
   struct EXP *exp;
   struct RECEIVER *receiver;
   struct ARGUMENT *argument;
   int modifier;
   int intconst;
   int boolconst;
   char charconst;
   char *stringconst;
};

%token tABSTRACT tBOOLEAN tBREAK tBYTE tCASE tCATCH tCHAR tCLASS tCONST
       tCONTINUE tDEFAULT tDO tDOUBLE tELSE tEXTENDS tEXTERN tFINAL 
       tFINALLY tFLOAT tFOR tGOTO tIF tIMPLEMENTS tIMPORT tIN tINSTANCEOF tINT 
       tINTERFACE tLONG tMAIN tMAINARGV tNATIVE tNEW tNULL tPACKAGE 
       tPRIVATE tPROTECTED tPUBLIC tRETURN tSHORT tSTATIC tSUPER 
       tSWITCH tSYNCHRONIZED tTHIS tTHROW tTHROWS tTRANSIENT tTRY tVOID 
       tVOLATILE tWHILE tEQ tLEQ tGEQ tNEQ tAND tOR tINC tPATH tERROR

%token <intconst> tINTCONST
%token <boolconst> tBOOLCONST
%token <charconst> tCHARCONST
%token <stringconst> tSTRINGCONST tIDENTIFIER

%type <classfile> classfile externclasses
%type <class> class externclass 
%type <field> fields nefields field
%type <type> type returntype
%type <id> idlist
%type <constructor> constructor externconstructor constructors externconstructors
%type <method> methods nemethods method 
%type <method> externmethods externnemethods externmethod
%type <formal> formals neformals formal
%type <statement> statements nestatements statement simplestatement
%type <statement> ifthenstatement whilestatement expressionstatement 
%type <statement> ifthenelsestatement returnstatement statementnoshortif 
%type <statement> ifthenelsestatementnoshortif whilestatementnoshortif 
%type <statement> declaration


/* added to support for loops */
%type <statement> forstatement forstatementnoshortif 
%type <statement> listassignexp nelistassignexp
%type <exp> listbooleanexp

/* increment */
%type <exp> incrementexpression



%type <exp> statementexpression assignment methodinvocation
%type <exp> classinstancecreation returnexpression expression orexpression 
%type <exp> andexpression eqexpression relexpression addexpression 
%type <exp> multexpression unaryexpression castexpression postfixexpression 
%type <exp> primaryexpression literal unaryexpressionnotminus 
%type <receiver> receiver
%type <argument> arguments nearguments 
%type <stringconst> extension 
%type <modifier> classmods methodmods externmods

%% /* productions */

classfile : imports class
            {theclassfile = makeCLASSFILE($2,NULL);}
          | externclasses
            {theclassfile = $1;}
;

imports : /* empty */
        | imports tPATH 
        ;

class : tPUBLIC classmods tCLASS tIDENTIFIER extension 
        '{' fields constructors methods '}'
        {$$ = makeCLASS($4,$5,0,NULL,$2,$7,$8,$9);}
;

classmods : /* empty */
            {$$ = noneMod;}
          | tFINAL
            {$$ = finalMod;}
          | tABSTRACT
            {$$ = abstractMod;}
;

externclasses : externclass
                {$$ = makeCLASSFILE($1,NULL);}
              | externclasses externclass
                {$$ = makeCLASSFILE($2,$1);}
;

externclass : tEXTERN tPUBLIC classmods tCLASS tIDENTIFIER extension 
              tIN tSTRINGCONST '{' externconstructors externmethods '}'
              {$$ = makeCLASS($5,$6,1,$8,$3,NULL,$10,$11);}
;

extension : /* empty */ 
            {$$ = NULL;}
          | tEXTENDS tIDENTIFIER
            {$$ = $2;}
;

type : tIDENTIFIER 
       {$$ = makeTYPEref($1);}
     | tCHAR
       {$$ = makeTYPEchar();}
     | tBOOLEAN 
       {$$ = makeTYPEbool();}
     | tINT 
       {$$ = makeTYPEint();}
;

fields : /* empty */ 
         {$$ = NULL;}
       | nefields
         {$$ = $1;}
;

nefields : field 
           {$$ = $1;}
         | nefields field
           {$$ = appendFIELD($2,$1);}
;

field : tPROTECTED type idlist ';' 
        {$$ = makeFIELDlist($3,$2);}
;

idlist : tIDENTIFIER 
         {$$ = makeID($1,NULL);}
       | idlist ',' tIDENTIFIER
         {$$ = makeID($3,$1);}
;

constructors : constructor
               {$$ = $1;}
             | constructors constructor
               {$$ = $2; $$->next = $1;}
;

constructor : tPUBLIC tIDENTIFIER '(' formals ')' 
              '{' tSUPER '(' arguments ')' ';' statements '}'
              {$$ = makeCONSTRUCTOR($2,$4,
                                    makeSTATEMENTsequence(
                                        makeSTATEMENTsupercons($9),
                                        $12
                                    ),
                                    NULL
                    );}
;

externconstructors : externconstructor
                     {$$ = $1;}
                   | externconstructors externconstructor
                     {$$ = $2; $$->next = $1;}
;

externconstructor : tPUBLIC tIDENTIFIER '(' formals ')' ';'
                    {$$ = makeCONSTRUCTOR($2,$4,NULL,NULL);}
;

formals : /* empty */ 
          {$$ = NULL;}
        | neformals
          {$$ = $1;}
;

neformals : formal 
            {$$ = $1;}
          | neformals ',' formal
            {$$ = $3; $$->next = $1;}
;

formal : type tIDENTIFIER
         {$$ = makeFORMAL($2,$1,NULL);}
;

methods : /* empty */ 
          {$$ = NULL;}
        | nemethods
          {$$ = $1;}
;

nemethods : method 
            {$$ = $1;}
          | nemethods method
            {$$ = $2; $$->next = $1;}
;

method : tPUBLIC methodmods returntype tIDENTIFIER '(' formals ')' '{' statements '}'
         {$$ = makeMETHOD($4,$2,$3,$6,$9,NULL);}
       | tPUBLIC returntype tIDENTIFIER '(' formals ')' '{' statements '}'
         {$$ = makeMETHOD($3,noneMod,$2,$5,$8,NULL);}
       | tPUBLIC tABSTRACT returntype tIDENTIFIER '(' formals ')' ';'
         {$$ = makeMETHOD($4,abstractMod,$3,$6,NULL,NULL);}
       | tPUBLIC tSTATIC tVOID tMAIN '(' mainargv ')' '{' statements '}'
         {$$ = makeMETHOD("main",staticMod,makeTYPEvoid(),NULL,$9,NULL);}
;

methodmods : tFINAL
             {$$ = finalMod;}
           | tSYNCHRONIZED
             {$$ = synchronizedMod;}
;

mainargv : tIDENTIFIER tIDENTIFIER '[' ']'
           {if (strcmp($1,"String")!=0) yyerror("type String expected");}
         | tIDENTIFIER '[' ']' tIDENTIFIER
           {if (strcmp($1,"String")!=0) yyerror("type String expected");}
         ;

externmethods : /* empty */
                {$$ = NULL;}
              | externnemethods
                {$$ = $1;}
;
 
externnemethods : externmethod
                  {$$ = $1;}
                | externnemethods externmethod
                  {$$ = $2; $$->next = $1;}
;
 
externmethod : tPUBLIC externmods returntype tIDENTIFIER '(' formals ')' ';'
               {$$ = makeMETHOD($4,$2,$3,$6,NULL,NULL);}
             | tPUBLIC returntype tIDENTIFIER '(' formals ')' ';'
               {$$ = makeMETHOD($3,noneMod,$2,$5,NULL,NULL);}
;

externmods : tFINAL
             {$$ = finalMod;}
           | tABSTRACT
             {$$ = abstractMod;}
           | tSYNCHRONIZED
             {$$ = synchronizedMod;}
;


returntype : tVOID 
             {$$ = makeTYPEvoid();}
           | type
             {$$ = $1;}
;

statements : /* empty */ 
             {$$ = NULL;}
           | nestatements
             {$$ = $1;}
;

nestatements : statement 
               {$$ = $1;}
             | nestatements statement
               {$$ = makeSTATEMENTsequence($1,$2);}
;

statement : simplestatement 
            {$$ = $1;}
          | declaration
            {$$ = $1;}
          | ifthenstatement 
            {$$ = $1;}
          | ifthenelsestatement 
            {$$ = $1;}
          | whilestatement
            {$$ = $1;}
          | forstatement       /* added */
            {$$ = $1;}
;

declaration : type idlist ';'
              {$$ = makeSTATEMENTlocal(makeLOCALlist($2,$1));}
;

simplestatement : ';' 
                  {$$ = makeSTATEMENTskip();}
                | '{' statements '}'
                  {$$ = makeSTATEMENTblock($2);}
                | expressionstatement 
                  {$$ = $1;}
                | returnstatement
                  {$$ = $1;}
;

ifthenstatement : tIF '(' expression ')' statement
                  {$$ = makeSTATEMENTif($3,$5);}
;

ifthenelsestatement : tIF '(' expression ')' statementnoshortif tELSE statement
                      {$$ = makeSTATEMENTifelse($3,$5,$7);}
;

statementnoshortif : simplestatement 
                     {$$ = $1;}
                   | ifthenelsestatementnoshortif 
                     {$$ = $1;}
                   | whilestatementnoshortif
                     {$$ = $1;}
                   | forstatementnoshortif     /* added */
                     {$$ = $1;}
;

ifthenelsestatementnoshortif : tIF '(' expression ')' statementnoshortif
                               tELSE statementnoshortif
                               {$$ = makeSTATEMENTifelse($3,$5,$7);}
;

whilestatement : tWHILE '(' expression ')' statement
                 {$$ = makeSTATEMENTwhile($3,$5);}
;

whilestatementnoshortif : tWHILE '(' expression ')' statementnoshortif
                          {$$ = makeSTATEMENTwhile($3,$5);}
;



/*
 * forstatement and forstatementnoshortif started by Richard,
 *  completed by David 2000/10/05
 *  Modified 2000/10/06 by David to make booleanexp optional in for loop 
 */

forstatement : tFOR '(' listassignexp ';' listbooleanexp ';' listassignexp ')' statement
                 {$$ = makeSTATEMENTsequence($3,makeSTATEMENTwhile($5,makeSTATEMENTsequence($9,$7)));}
;


forstatementnoshortif : tFOR '(' listassignexp ';' listbooleanexp ';' listassignexp ')' statementnoshortif
                 {$$ = makeSTATEMENTsequence($3,makeSTATEMENTwhile($5,makeSTATEMENTsequence($9,$7)));}
;

/* grammar rules for comma separated lists in for-loop */
listassignexp : /* empty */         { $$ = NULL; }
                | nelistassignexp   { $$ = $1; }

nelistassignexp : statementexpression  { $$ = makeSTATEMENTexp($1); }
                  | nelistassignexp ',' statementexpression
                     { $$ = makeSTATEMENTsequence($1, makeSTATEMENTexp($3)); }

listbooleanexp : /* empty ==> true */  { $$ = makeEXPboolconst(1); }
                 | expression          { $$ = $1; }




/*Production for increment
  Added by Tudor

  Modified by David (makeEXPintconst added)
*/
incrementexpression : tIDENTIFIER tINC
                {$$ = makeEXPassign($1, makeEXPplus(makeEXPid($1),makeEXPintconst(1))); }







expressionstatement : statementexpression ';'
                      {$$ = makeSTATEMENTexp($1);}
;

statementexpression : assignment 
                      {$$ = $1;}
                    | methodinvocation 
                      {$$ = $1;}
                    | classinstancecreation
                      {$$ = $1;}
                    | incrementexpression { $$ = $1; }  /* added by David */
;

returnstatement : tRETURN returnexpression ';'
                  {$$ = makeSTATEMENTreturn($2);}
;

returnexpression : /* empty */ 
                   {$$ = NULL;}
                 | expression
                   {$$ = $1;}
;

assignment : tIDENTIFIER '=' expression
             {$$ = makeEXPassign($1,$3);}
;

expression : orexpression 
             {$$ = $1;}
           | assignment
             {$$ = $1;}
;

orexpression : andexpression 
               {$$ = $1;}
             | orexpression tOR andexpression
               {$$ = makeEXPor($1,$3);}
;

andexpression : eqexpression 
                {$$ = $1;}
              | andexpression tAND eqexpression
                {$$ = makeEXPand($1,$3);}
;

eqexpression : relexpression 
               {$$ = $1;}
             | eqexpression tEQ relexpression 
               {$$ = makeEXPeq($1,$3);}
             | eqexpression tNEQ relexpression
               {$$ = makeEXPneq($1,$3);}
;

relexpression : addexpression 
                {$$ = $1;}
              | relexpression '<' addexpression 
                {$$ = makeEXPlt($1,$3);}
              | relexpression '>' addexpression 
                {$$ = makeEXPgt($1,$3);}
              | relexpression tLEQ addexpression 
                {$$ = makeEXPleq($1,$3);}
              | relexpression tGEQ addexpression 
                {$$ = makeEXPgeq($1,$3);}
              | relexpression tINSTANCEOF tIDENTIFIER
                {$$ = makeEXPinstanceof($1,$3);}


addexpression : multexpression 
                {$$ = $1;}
              | addexpression '+' multexpression 
                {$$ = makeEXPplus($1,$3);}
              | addexpression '-' multexpression
                {$$ = makeEXPminus($1,$3);}




multexpression : unaryexpression 
                 {$$ = $1;}
               | multexpression '*' unaryexpression 
                 {$$ = makeEXPtimes($1,$3);}
               | multexpression '/' unaryexpression 
                 {$$ = makeEXPdiv($1,$3);}
               | multexpression '%' unaryexpression
                 {$$ = makeEXPmod($1,$3);}
;

unaryexpression : unaryexpressionnotminus 
                  {$$ = $1;}
                | '-' unaryexpression 
                  {$$ = makeEXPuminus($2);}
;

unaryexpressionnotminus : 
                  postfixexpression
                  {$$ = $1;}
                | '!' unaryexpression
                  {$$ = makeEXPnot($2);}
                | castexpression
                  {$$ = $1;}

castexpression : '(' expression ')' unaryexpressionnotminus
                 {if ($2->kind!=idK) yyerror("identifier expected");
                  $$ = makeEXPcast($2->val.idE.name,$4);}
               | '(' tCHAR ')' unaryexpression
                 {$$ = makeEXPcharcast($4);}
;

postfixexpression : tIDENTIFIER 
                    {$$ = makeEXPid($1);}
                  | primaryexpression
                    {$$ = $1;}
;

primaryexpression : literal 
                    {$$ = $1;}
                  | tTHIS 
                    {$$ = makeEXPthis();}
                  | '(' expression ')' 
                    {$$ = $2;}
                  | classinstancecreation 
                    {$$ = $1;}
                  | methodinvocation
                    {$$ = $1;}
;

classinstancecreation : tNEW tIDENTIFIER '(' arguments ')'
                        {$$ = makeEXPnew($2,$4);}
;

methodinvocation : receiver '.' tIDENTIFIER '(' arguments ')'
                   {$$ = makeEXPinvoke($1,$3,$5);}
;

receiver : tIDENTIFIER 
           {$$ = makeRECEIVERobject(makeEXPid($1));}
         | primaryexpression 
           {$$ = makeRECEIVERobject($1);}
         | tSUPER
           {$$ = makeRECEIVERsuper();}
;
 
arguments : /* empty */ 
            {$$ = NULL;}
          | nearguments
            {$$ = $1;}
;

nearguments : expression 
              {$$ = makeARGUMENT($1,NULL);}
            | nearguments ',' expression
              {$$ = makeARGUMENT($3,$1);}
;

literal : tINTCONST 
          {$$ = makeEXPintconst($1);}
        | tBOOLCONST 
          {$$ = makeEXPboolconst($1);}
        | tCHARCONST
          {$$ = makeEXPcharconst($1);}
        | tSTRINGCONST 
          {$$ = makeEXPstringconst($1);}
        | tNULL
          {$$ = makeEXPnull();}
;

