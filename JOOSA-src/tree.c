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

#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "tree.h"
 
extern int lineno;

PROGRAM *makePROGRAM(char *name, CLASSFILE *classfile, PROGRAM *next)
{ PROGRAM *p;
  p = NEW(PROGRAM);
  p->name = name;
  p->classfile = classfile;
  p->next = next;
  return p;
}

CLASSFILE *makeCLASSFILE(CLASS *class, CLASSFILE *next)
{ CLASSFILE *c;
  c = NEW(CLASSFILE);
  c->class = class;
  c->next = next;
  return c;
}

CLASS *makeCLASS(char *name, char *parentname, 
                 int external, char *package, ModifierKind modifier,
                 FIELD *fields, CONSTRUCTOR *constructors, METHOD *methods)
{ CLASS *c;
  c = NEW(CLASS);
  c->lineno = lineno;
  c->name = name;
  if (parentname==NULL && (strcmp(name,"Object")!=0)) {
     c->parentname = "Object";
  } else {
     c->parentname = parentname;
  }
  c->external = external;
  c->package = package;
  c->modifier = modifier;
  c->fields = fields;
  c->constructors = constructors;
  c->methods = methods;
  return c;
}

FIELD *makeFIELD(char *name, TYPE *type, FIELD *next)
{ FIELD *f;
  f = NEW(FIELD);
  f->lineno = lineno;
  f->name = name;
  f->type = type;
  f->next = next;
  return f;
}

FIELD *makeFIELDlist(ID *names, TYPE *type)
{ if (names==NULL) return NULL;
  return makeFIELD(names->name,type,makeFIELDlist(names->next,type));
}

FIELD *appendFIELD(FIELD *f, FIELD *g)
{ FIELD *t;
  if (f==NULL) return g;
  t = f;
  while (t->next!=NULL) t = t->next;
  t->next = g;
  return f;
}

TYPE *makeTYPEint()
{ TYPE *t;
  t = NEW(TYPE);
  t->lineno = lineno;
  t->kind = intK;
  return t;
}

TYPE *makeTYPEbool()
{ TYPE *t;
  t = NEW(TYPE);
  t->lineno = lineno;
  t->kind = boolK;
  return t;
}

TYPE *makeTYPEchar()
{ TYPE *t;
  t = NEW(TYPE);
  t->lineno = lineno;
  t->kind = charK;
  return t;
}

TYPE *makeTYPEvoid()
{ TYPE *t;
  t = NEW(TYPE);
  t->lineno = lineno;
  t->kind = voidK;
  return t;
}

TYPE *makeTYPEref(char *name)
{ TYPE *t;
  t = NEW(TYPE);
  t->lineno = lineno;
  t->kind = refK;
  t->name = name;
  return t;
}

TYPE *makeTYPEextref(char *name, CLASS *c) 
{ TYPE *t;
  t = makeTYPEref(name);
  t->class = c;
  return t;
}

ID *makeID(char *name, ID *next)
{ ID *i;
  i = NEW(ID);
  i->name = name;
  i->next = next;
  return i;
}

CONSTRUCTOR *makeCONSTRUCTOR(char *name, FORMAL *formals, STATEMENT *statements, CONSTRUCTOR *next)
{ CONSTRUCTOR *c;
  c = NEW(CONSTRUCTOR);
  c->lineno = lineno;
  c->name = name;
  c->formals = formals;
  c->statements = statements;
  c->next = next;
  return c;
}

METHOD *makeMETHOD(char *name, ModifierKind modifier, TYPE *returntype, 
                   FORMAL *formals, STATEMENT *statements, METHOD *next)
{ METHOD *m;
  m = NEW(METHOD);
  m->lineno = lineno;
  m->name = name;
  m->modifier = modifier;
  m->returntype = returntype;
  m->formals = formals;
  m->statements = statements;
  m->next = next;
  return m;
}

FORMAL *makeFORMAL(char *name, TYPE *type, FORMAL *next)
{ FORMAL *f;
  f = NEW(FORMAL);
  f->lineno = lineno;
  f->name = name;
  f->type = type;
  f->next = next;
  return f;
}

LOCAL *makeLOCAL(char *name, TYPE *type, LOCAL *next)
{ LOCAL *l;
  l = NEW(LOCAL);
  l->lineno = lineno;
  l->name = name;
  l->type = type;
  l->next = next;
  return l;
}

LOCAL *makeLOCALlist(ID *names, TYPE *type)
{ if (names==NULL) return NULL;
  return makeLOCAL(names->name,type,makeLOCALlist(names->next,type));
}

STATEMENT *makeSTATEMENTskip()
{ STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = skipK;
  return s;
}

STATEMENT *makeSTATEMENTexp(EXP *exp)
{ STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = expK;
  s->val.expS = exp;
  return s;
}

STATEMENT *makeSTATEMENTlocal(LOCAL *locals)
{ STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = localK;
  s->val.localS = locals;
  return s;
}

STATEMENT *makeSTATEMENTreturn(EXP *exp)
{ STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = returnK;
  s->val.returnS = exp;
  return s;
}

STATEMENT *makeSTATEMENTsequence(STATEMENT *first, STATEMENT *second)
{ STATEMENT *s;
  if (first==NULL) return second;
  if (second==NULL) return first;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = sequenceK;
  s->val.sequenceS.first = first;
  s->val.sequenceS.second = second;
  return s;
}

STATEMENT *makeSTATEMENTif(EXP *condition, STATEMENT *body)
{ STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = ifK;
  s->val.ifS.condition = condition;
  s->val.ifS.body = body;
  return s;
}

STATEMENT *makeSTATEMENTifelse(EXP *condition,
                               STATEMENT *thenpart,
                               STATEMENT *elsepart)
{ STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = ifelseK;
  s->val.ifelseS.condition = condition;
  s->val.ifelseS.thenpart = thenpart;
  s->val.ifelseS.elsepart = elsepart;
  return s;
}

STATEMENT *makeSTATEMENTwhile(EXP *condition, STATEMENT *body)
{ STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = whileK;
  s->val.whileS.condition = condition;
  s->val.whileS.body = body;
  return s;
}

STATEMENT *makeSTATEMENTblock(STATEMENT *body)
{STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = blockK;
  s->val.blockS.body = body;  
  return s;
}

STATEMENT *makeSTATEMENTsupercons(ARGUMENT *args)
{STATEMENT *s;
  s = NEW(STATEMENT);
  s->lineno = lineno;
  s->kind = superconsK;
  s->val.superconsS.args = args;
  return s;
}

EXP *makeEXPid(char *name)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = idK;
  e->val.idE.name = name;
  return e;
}

EXP *makeEXPassign(char *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = assignK;
  e->val.assignE.left = left;
  e->val.assignE.right = right;
  return e;
}

EXP *makeEXPor(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = orK;
  e->val.orE.left = left;
  e->val.orE.right = right;
  return e;
}

EXP *makeEXPand(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = andK;
  e->val.andE.left = left;
  e->val.andE.right = right;
  return e;
}

EXP *makeEXPeq(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = eqK;
  e->val.eqE.left = left;
  e->val.eqE.right = right;
  return e;
}

EXP *makeEXPlt(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = ltK;
  e->val.ltE.left = left;
  e->val.ltE.right = right;
  return e;
}

EXP *makeEXPgt(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = gtK;
  e->val.gtE.left = left;
  e->val.gtE.right = right;
  return e;
}

EXP *makeEXPleq(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = leqK;
  e->val.leqE.left = left;
  e->val.leqE.right = right;
  return e;
}

EXP *makeEXPgeq(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = geqK;
  e->val.geqE.left = left;
  e->val.geqE.right = right;
  return e;
}

EXP *makeEXPneq(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = neqK;
  e->val.neqE.left = left;
  e->val.neqE.right = right;
  return e;
}

EXP *makeEXPinstanceof(EXP *left, char *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = instanceofK;
  e->val.instanceofE.left = left;
  e->val.instanceofE.right = right;
  return e;
}

EXP *makeEXPplus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = plusK;
  e->val.plusE.left = left;
  e->val.plusE.right = right;
  return e;
}

EXP *makeEXPminus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = minusK;
  e->val.minusE.left = left;
  e->val.minusE.right = right;
  return e;
}

EXP *makeEXPtimes(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = timesK;
  e->val.timesE.left = left;
  e->val.timesE.right = right;
  return e;
}

EXP *makeEXPdiv(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = divK;
  e->val.divE.left = left;
  e->val.divE.right = right;
  return e;
}

EXP *makeEXPmod(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = modK;
  e->val.modE.left = left;
  e->val.modE.right = right;
  return e;
}

EXP *makeEXPnot(EXP *not)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = notK;
  e->val.notE.not = not;
  return e;
}

EXP *makeEXPuminus(EXP *uminus)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = uminusK;
  e->val.uminusE = uminus;
  return e;
}

EXP *makeEXPthis()
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = thisK;
  return e;
}

EXP *makeEXPnew(char *name, ARGUMENT *args)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = newK;
  e->val.newE.name = name;
  e->val.newE.args = args;
  return e;
}

EXP *makeEXPinvoke(RECEIVER *receiver, char *name, ARGUMENT *args)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = invokeK;
  e->val.invokeE.receiver = receiver;
  e->val.invokeE.name = name;
  e->val.invokeE.args = args;
  return e;
}

EXP *makeEXPintconst(int intconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = intconstK;
  e->val.intconstE = intconst;
  return e;
}

EXP *makeEXPboolconst(int boolconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = boolconstK;
  e->val.boolconstE = boolconst;
  return e;
}

EXP *makeEXPcharconst(char charconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = charconstK;
  e->val.charconstE = charconst;
  return e;
}

EXP *makeEXPstringconst(char *stringconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = stringconstK;
  e->val.stringconstE = stringconst;
  return e;
}

EXP *makeEXPnull()
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = nullK;
  return e;
}

EXP *makeEXPcast(char *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = castK;
  e->val.castE.left = left;
  e->val.castE.right = right;
  return e;
}

EXP *makeEXPcharcast(EXP *charcast)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = lineno;
  e->tostring = 0;
  e->kind = charcastK;
  e->val.charcastE = charcast;
  return e;
}

RECEIVER *makeRECEIVERobject(EXP *object)
{ RECEIVER *r;
  r = NEW(RECEIVER);
  r->lineno = lineno;
  r->kind = objectK;
  r->objectR = object;
  return r;
}

RECEIVER *makeRECEIVERsuper()
{ RECEIVER *r;
  r = NEW(RECEIVER);
  r->lineno = lineno;
  r->kind = superK;
  return r;
}

ARGUMENT *makeARGUMENT(EXP *exp, ARGUMENT *next)
{ ARGUMENT *a;
  a = NEW(ARGUMENT);
  a->exp = exp;
  a->next = next;
  return a;
}

CODE *makeCODEnop(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = nopCK;
  c->visited = 0;
  c->next = next;
  return c;
}

CODE *makeCODEi2c(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = i2cCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEnew(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = newCK;
  c->visited = 0;
  c->val.newC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEinstanceof(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = instanceofCK;
  c->visited = 0;
  c->val.instanceofC = arg;
  c->next = next;
  return c;
}
CODE *makeCODEcheckcast(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = checkcastCK;
  c->visited = 0;
  c->val.checkcastC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEimul(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = imulCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEineg(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = inegCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEirem(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = iremCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEisub(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = isubCK;
  c->visited = 0;
  c->next = next;
  return c;
}

CODE *makeCODEidiv(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = idivCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEiadd(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = iaddCK;
  c->visited = 0;
  c->next = next;
  return c;
}

CODE *makeCODEiinc(int offset, int amount, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = iincCK;
  c->visited = 0;
  c->val.iincC.offset = offset;
  c->val.iincC.amount = amount;
  c->next = next;
  return c;
}

CODE *makeCODElabel(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = labelCK;
  c->visited = 0;
  c->val.labelC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEgoto(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = gotoCK;
  c->visited = 0;
  c->val.gotoC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEifeq(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = ifeqCK;
  c->visited = 0;
  c->val.ifeqC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEifne(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = ifneCK;
  c->visited = 0;
  c->val.ifneC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_acmpeq(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_acmpeqCK;
  c->visited = 0;
  c->val.if_acmpeqC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_acmpne(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_acmpneCK;
  c->visited = 0;
  c->val.if_acmpneC = label;
  c->next = next;
  return c;
}

CODE *makeCODEifnull(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = ifnullCK;
  c->visited = 0;
  c->val.ifnullC = label;
  c->next = next;
  return c;
}

CODE *makeCODEifnonnull(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = ifnonnullCK;
  c->visited = 0;
  c->val.ifnonnullC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_icmpeq(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_icmpeqCK;
  c->visited = 0;
  c->val.if_icmpeqC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_icmpgt(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_icmpgtCK;
  c->visited = 0;
  c->val.if_icmpgtC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_icmplt(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_icmpltCK;
  c->visited = 0;
  c->val.if_icmpltC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_icmple(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_icmpleCK;
  c->visited = 0;
  c->val.if_icmpleC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_icmpge(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_icmpgeCK;
  c->visited = 0;
  c->val.if_icmpgeC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEif_icmpne(int label, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = if_icmpneCK;
  c->visited = 0;
  c->val.if_icmpneC = label;
  c->next = next;
  return c;
}
 
CODE *makeCODEireturn(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = ireturnCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEareturn(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = areturnCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEreturn(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = returnCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEaload(int arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = aloadCK;
  c->visited = 0;
  c->val.aloadC = arg;
  c->next = next;
  return c;
}

CODE *makeCODEastore(int arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = astoreCK;
  c->visited = 0;
  c->val.astoreC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEiload(int arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = iloadCK;
  c->visited = 0;
  c->val.iloadC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEistore(int arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = istoreCK;
  c->visited = 0;
  c->val.istoreC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEdup(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = dupCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEpop(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = popCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEswap(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = swapCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEldc_int(int arg, CODE *next)
{ CODE *c;
  c = NEW(CODE); 
  c->kind = ldc_intCK; 
  c->visited = 0;
  c->val.ldc_intC = arg; 
  c->next = next;
  return c;
}
 
CODE *makeCODEldc_string(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = ldc_stringCK;
  c->visited = 0;
  c->val.ldc_stringC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEaconst_null(CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = aconst_nullCK;
  c->visited = 0;
  c->next = next;
  return c;
}
 
CODE *makeCODEgetfield(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = getfieldCK;
  c->visited = 0;
  c->val.getfieldC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEputfield(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = putfieldCK;
  c->visited = 0;
  c->val.putfieldC = arg;
  c->next = next;
  return c;
}
 
CODE *makeCODEinvokevirtual(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = invokevirtualCK;
  c->visited = 0;
  c->val.invokevirtualC = arg;
  c->next = next;
  return c;
}

CODE *makeCODEinvokenonvirtual(char *arg, CODE *next)
{ CODE *c;
  c = NEW(CODE);
  c->kind = invokenonvirtualCK;
  c->visited = 0;
  c->val.invokenonvirtualC = arg;
  c->next = next;
  return c;
}
 
