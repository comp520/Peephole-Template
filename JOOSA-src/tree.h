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

#ifndef __tree_h
#define __tree_h

typedef enum{noneMod,finalMod,abstractMod,synchronizedMod,staticMod} ModifierKind;

typedef enum{classSym,fieldSym,methodSym,formalSym,localSym} SymbolKind;
 
typedef struct SYMBOL {
    char *name;
    SymbolKind kind;
    union {
      struct CLASS *classS;
      struct FIELD *fieldS;
      struct METHOD *methodS;
      struct FORMAL *formalS;
      struct LOCAL *localS;
    } val;
    struct SYMBOL *next;
} SYMBOL; 

typedef struct PROGRAM {
  char *name;
  struct CLASSFILE *classfile;
  struct PROGRAM *next;
} PROGRAM;

typedef struct CLASSFILE {
  struct CLASS *class;
  struct CLASSFILE *next;
} CLASSFILE;

typedef struct CLASS {
  int lineno;
  char *name;
  char *parentname;
  int external;
  char *package;
  ModifierKind modifier;
  struct FIELD *fields;
  struct CONSTRUCTOR *constructors;
  struct METHOD *methods;
  struct CLASS *parent; /* symbol */
  struct SymbolTable *localsym; /* symbol */
  char *signature; /* code */
} CLASS;

typedef struct FIELD {
  int lineno;
  char *name;
  struct TYPE *type;
  int offset; /* resource */
  struct FIELD *next;
} FIELD;

typedef struct TYPE {
  int lineno;
  enum {intK,boolK,charK,refK,voidK,polynullK} kind;  
  char *name;
  struct CLASS *class; /* symbol */
} TYPE;

typedef struct ID {
  char *name;
  struct ID *next;
} ID;

typedef struct CONSTRUCTOR {
  int lineno;
  char *name;
  struct FORMAL *formals;
  struct STATEMENT *statements;
  int localslimit; /* resource */
  int labelcount; /* resource */
  char *signature; /* code */
  struct LABEL *labels; /* code */
  struct CODE *opcodes; /* code */
  struct CONSTRUCTOR *next;
} CONSTRUCTOR;

typedef struct METHOD {
  int lineno;
  char *name;
  ModifierKind modifier; 
  struct TYPE *returntype;
  struct FORMAL *formals;
  struct STATEMENT *statements;
  int localslimit; /* resource */
  int labelcount; /* resource */
  char *signature; /* code */
  struct LABEL *labels; /* code */
  struct CODE *opcodes; /* code */
  struct METHOD *next;
} METHOD;

typedef struct FORMAL {
  int lineno;
  char *name;
  struct TYPE *type;
  int offset; /* resource */
  struct FORMAL *next;
} FORMAL;

typedef struct LOCAL {
  int lineno;
  char *name;
  struct TYPE *type;
  int offset; /* resource */
  struct LOCAL *next;
} LOCAL;

typedef struct STATEMENT {
  int lineno;
  enum {skipK,localK,expK,returnK,sequenceK,
        ifK,ifelseK,whileK,blockK,superconsK} kind;
  union{
    struct EXP *expS;
    struct LOCAL *localS;
    struct EXP *returnS;
    struct {struct STATEMENT *first;
            struct STATEMENT *second;} sequenceS;
    struct {struct EXP *condition; 
            struct STATEMENT *body;
            int stoplabel; /* resource */} ifS;
    struct {struct EXP *condition;
            struct STATEMENT *thenpart;
            struct STATEMENT *elsepart;
            int elselabel,stoplabel; /* resource */} ifelseS;
    struct {struct EXP *condition; 
            struct STATEMENT *body;
            int startlabel,stoplabel; /* resource */} whileS;
    struct {struct STATEMENT *body;} blockS;
    struct {struct ARGUMENT *args;
            struct CONSTRUCTOR *constructor; /* type */} superconsS;
  } val;
} STATEMENT;

typedef struct EXP {
  int lineno;
  TYPE *type;
  int tostring;
  int nulllabel,stoplabel;
  enum {idK,assignK,orK,andK,eqK,ltK,gtK,leqK,geqK,neqK,instanceofK,plusK,
        minusK,timesK,divK,modK,notK,uminusK,thisK,newK,invokeK,intconstK,
        boolconstK,charconstK,stringconstK,nullK,castK,charcastK} kind;
  union {
    struct {char *name; 
            SYMBOL *idsym; /* symbol */} idE;
    struct {char *left; 
            SYMBOL *leftsym; /* symbol */ 
            struct EXP *right;} assignE;
    struct {struct EXP *left; 
            struct EXP *right;
            int truelabel; /* resource */} orE;
    struct {struct EXP *left; 
            struct EXP *right;
            int falselabel; /* resource */} andE;
    struct {struct EXP *left; 
            struct EXP *right; 
            int truelabel,stoplabel; /* resource */} eqE;
    struct {struct EXP *left; 
            struct EXP *right;
            int truelabel,stoplabel; /* resource */} ltE;
    struct {struct EXP *left; 
            struct EXP *right;
            int truelabel,stoplabel; /* resource */} gtE;
    struct {struct EXP *left; 
            struct EXP *right;
            int truelabel,stoplabel; /* resource */} leqE;
    struct {struct EXP *left; 
            struct EXP *right;
            int truelabel,stoplabel; /* resource */} geqE;
    struct {struct EXP *left; 
            struct EXP *right;
            int truelabel,stoplabel; /* resource */} neqE;
    struct {struct EXP *left; 
            char *right; 
            struct CLASS *class; /* symbol */} instanceofE;
    struct {struct EXP *left; struct EXP *right;} plusE;
    struct {struct EXP *left; struct EXP *right;} minusE;
    struct {struct EXP *left; struct EXP *right;} timesE;
    struct {struct EXP *left; struct EXP *right;} divE;
    struct {struct EXP *left; struct EXP *right;} modE;
    struct {struct EXP *not;
            int truelabel,stoplabel; /* resource */} notE;
    struct EXP *uminusE;
    struct {char *name; 
            struct CLASS *class; /* symbol */
            struct CONSTRUCTOR *constructor; /* type */
            struct ARGUMENT *args;} newE;
    struct {struct RECEIVER *receiver; 
            char *name; 
            struct METHOD *method; /* type */
            struct ARGUMENT *args;} invokeE;
    int intconstE;
    int boolconstE;
    char charconstE;
    char *stringconstE;
    struct {char *left; 
            struct CLASS *class; /* symbol */
            struct EXP *right;} castE;
    struct EXP *charcastE;
  } val;
} EXP;

typedef struct RECEIVER {
  int lineno;
  enum {objectK,superK} kind;
  struct EXP *objectR;
} RECEIVER;

typedef struct ARGUMENT {
   struct EXP *exp;
   struct ARGUMENT *next;
} ARGUMENT;

typedef struct LABEL {
   char *name;
   int sources;
   struct CODE *position;
} LABEL;

typedef struct CODE {
   enum {nopCK,i2cCK,
         newCK,instanceofCK,checkcastCK,
         imulCK,inegCK,iremCK,isubCK,idivCK,iaddCK,iincCK,
         labelCK,gotoCK,ifeqCK,ifneCK,if_acmpeqCK,if_acmpneCK,
         ifnullCK,ifnonnullCK,
         if_icmpeqCK,if_icmpgtCK,if_icmpltCK,
         if_icmpleCK,if_icmpgeCK,if_icmpneCK,
         ireturnCK,areturnCK,returnCK,
         aloadCK,astoreCK,iloadCK,istoreCK,dupCK,popCK,swapCK,
         ldc_intCK,ldc_stringCK,aconst_nullCK,
         getfieldCK,putfieldCK,invokevirtualCK,invokenonvirtualCK} kind;
   int visited; /* emit */
   union {
     char *newC;
     char *instanceofC;
     char *checkcastC;
     struct {int offset; int amount;} iincC;
     int labelC;
     int gotoC;
     int ifeqC;
     int ifneC;
     int if_acmpeqC;
     int if_acmpneC;
     int ifnullC;
     int ifnonnullC;
     int if_icmpeqC;
     int if_icmpgtC;
     int if_icmpltC;
     int if_icmpleC;
     int if_icmpgeC;
     int if_icmpneC;
     int aloadC;
     int astoreC;
     int iloadC;
     int istoreC;
     int ldc_intC;
     char *ldc_stringC;
     char *getfieldC;
     char *putfieldC;
     char *invokevirtualC;
     char *invokenonvirtualC;
   } val;
   struct CODE *next;
} CODE;

PROGRAM *makePROGRAM(char *name, CLASSFILE *classfile, PROGRAM *next);
CLASSFILE *makeCLASSFILE(CLASS *class, CLASSFILE *next);
CLASS *makeCLASS(char *name, char *parentname, 
                 int external, char *package, ModifierKind modifier,
                 FIELD *fields, CONSTRUCTOR *constructors, METHOD *methods);
FIELD *makeFIELD(char *name, TYPE *type, FIELD *next);
FIELD *makeFIELDlist(ID *names, TYPE *type);
FIELD *appendFIELD(FIELD *f, FIELD *g);
TYPE *makeTYPEint();
TYPE *makeTYPEbool();
TYPE *makeTYPEchar();
TYPE *makeTYPEvoid();
TYPE *makeTYPEref(char *name);
TYPE *makeTYPEextref(char *name, CLASS *c);
ID *makeID(char *name, ID *next);
CONSTRUCTOR *makeCONSTRUCTOR(char *name, FORMAL *formals, STATEMENT *statements, CONSTRUCTOR *next);
METHOD *makeMETHOD(char *name, ModifierKind modifier, TYPE *returntype, 
                   FORMAL *formals, STATEMENT *statements, METHOD *next);
FORMAL *makeFORMAL(char *name, TYPE *type, FORMAL *next);
LOCAL *makeLOCAL(char *name, TYPE *type, LOCAL *next);
LOCAL *makeLOCALlist(ID *names, TYPE *type);
STATEMENT *makeSTATEMENTskip();
STATEMENT *makeSTATEMENTexp(EXP *exp);
STATEMENT *makeSTATEMENTlocal(LOCAL *locals);
STATEMENT *makeSTATEMENTreturn(EXP *exp);
STATEMENT *makeSTATEMENTsequence(STATEMENT *first, STATEMENT *second);
STATEMENT *makeSTATEMENTif(EXP *condition, STATEMENT *body);
STATEMENT *makeSTATEMENTifelse(EXP *condition,
                               STATEMENT *thenpart,
                               STATEMENT *elsepart);
STATEMENT *makeSTATEMENTwhile(EXP *condition, STATEMENT *body);
STATEMENT *makeSTATEMENTblock(STATEMENT *body);
STATEMENT *makeSTATEMENTsupercons(ARGUMENT *args);
EXP *makeEXPid(char *name);
EXP *makeEXPassign(char *left, EXP *right);
EXP *makeEXPor(EXP *left, EXP *right);
EXP *makeEXPand(EXP *left, EXP *right);
EXP *makeEXPeq(EXP *left, EXP *right);
EXP *makeEXPlt(EXP *left, EXP *right);
EXP *makeEXPgt(EXP *left, EXP *right);
EXP *makeEXPleq(EXP *left, EXP *right);
EXP *makeEXPgeq(EXP *left, EXP *right);
EXP *makeEXPneq(EXP *left, EXP *right);
EXP *makeEXPinstanceof(EXP *left, char *right);
EXP *makeEXPplus(EXP *left, EXP *right);
EXP *makeEXPminus(EXP *left, EXP *right);
EXP *makeEXPtimes(EXP *left, EXP *right);
EXP *makeEXPdiv(EXP *left, EXP *right);
EXP *makeEXPmod(EXP *left, EXP *right);
EXP *makeEXPnot(EXP *not);
EXP *makeEXPuminus(EXP *uminus);
EXP *makeEXPthis();
EXP *makeEXPnew(char *name, ARGUMENT *args);
EXP *makeEXPinvoke(RECEIVER *receiver, char *name, ARGUMENT *args);
EXP *makeEXPintconst(int intconst);
EXP *makeEXPboolconst(int boolconst);
EXP *makeEXPcharconst(char charconst);
EXP *makeEXPstringconst(char *stringconst);
EXP *makeEXPnull();
EXP *makeEXPcast(char *name, EXP *arg);
EXP *makeEXPcharcast(EXP *charcast);
RECEIVER *makeRECEIVERobject(EXP *object);
RECEIVER *makeRECEIVERsuper();
ARGUMENT *makeARGUMENT(EXP *exp, ARGUMENT *next);
CODE *makeCODEnop(CODE *next);
CODE *makeCODEi2c(CODE *next);
CODE *makeCODEnew(char *arg, CODE *next);
CODE *makeCODEinstanceof(char *arg, CODE *next);
CODE *makeCODEcheckcast(char *arg, CODE *next);
CODE *makeCODEimul(CODE *next);
CODE *makeCODEineg(CODE *next);
CODE *makeCODEirem(CODE *next);
CODE *makeCODEisub(CODE *next);
CODE *makeCODEidiv(CODE *next);
CODE *makeCODEiadd(CODE *next);
CODE *makeCODEiinc(int offset, int amount, CODE *next);
CODE *makeCODElabel(int label, CODE *next);
CODE *makeCODEgoto(int label, CODE *next);
CODE *makeCODEifeq(int label, CODE *next);
CODE *makeCODEifne(int label, CODE *next);
CODE *makeCODEif_acmpeq(int label, CODE *next);
CODE *makeCODEif_acmpne(int label, CODE *next);
CODE *makeCODEifnull(int label, CODE *next);
CODE *makeCODEifnonnull(int label, CODE *next);
CODE *makeCODEif_icmpeq(int label, CODE *next);
CODE *makeCODEif_icmpgt(int label, CODE *next);
CODE *makeCODEif_icmplt(int label, CODE *next);
CODE *makeCODEif_icmple(int label, CODE *next);
CODE *makeCODEif_icmpge(int label, CODE *next);
CODE *makeCODEif_icmpne(int label, CODE *next);
CODE *makeCODEireturn(CODE *next);
CODE *makeCODEareturn(CODE *next);
CODE *makeCODEreturn(CODE *next);
CODE *makeCODEaload(int arg, CODE *next);
CODE *makeCODEastore(int arg, CODE *next);
CODE *makeCODEiload(int arg, CODE *next);
CODE *makeCODEistore(int arg, CODE *next);
CODE *makeCODEdup(CODE *next);
CODE *makeCODEpop(CODE *next);
CODE *makeCODEswap(CODE *next);
CODE *makeCODEldc_int(int arg, CODE *next);
CODE *makeCODEldc_string(char *arg, CODE *next);
CODE *makeCODEaconst_null(CODE *next);
CODE *makeCODEgetfield(char *arg, CODE *next);
CODE *makeCODEputfield(char *arg, CODE *next);
CODE *makeCODEinvokevirtual(char *arg, CODE *next);
CODE *makeCODEinvokenonvirtual(char *arg, CODE *next);

#endif
