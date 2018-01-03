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
#include "error.h"
#include "weed.h"

extern char *currentfile;

void weedPROGRAM(PROGRAM *p)
{ if (p!=NULL) {
     weedPROGRAM(p->next);
     currentfile = p->name;
     weedCLASSFILE(p->classfile);
  }
}

void weedCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
      weedCLASSFILE(c->next);
      weedCLASS(c->class);
  }
}

void weedCLASS(CLASS *c)
{ weedCONSTRUCTOR(c->constructors);
  weedMETHOD(c->methods,c->modifier,c->external);
}

void weedCONSTRUCTOR(CONSTRUCTOR *c)
{ if (c!=NULL) {
     weedCONSTRUCTOR(c->next);
     (void)weedSTATEMENTlocals(c->statements,1);
  }
}

void weedMETHOD(METHOD *m, ModifierKind classmod, int external)
{ if (m!=NULL) {
      weedMETHOD(m->next,classmod,external);
      if (m->modifier==abstractMod && classmod!=abstractMod) {
         reportStrError("abstract method %s requires an abstract class",
                        m->name,m->lineno);
      }
      if (m->modifier==staticMod) {
         weedSTATEMENTmain(m->statements);
      }
      (void)weedSTATEMENTlocals(m->statements,1);
      if (m->returntype->kind!=voidK && !external && m->modifier!=abstractMod) {
         if (m->statements==NULL || !weedSTATEMENTreturns(m->statements))
            reportStrError("method %s must return a value",m->name,m->lineno);
      }
   }
}

int weedSTATEMENTlocals(STATEMENT *s,int localsallowed)
{ int onlylocalsfirst, onlylocalssecond;
  if (s!=NULL) {
     switch (s->kind) {
       case skipK:
            break;
       case localK:
            if (!localsallowed) {
               reportError("illegally placed local declaration",s->lineno);
            }
            return 1;
            break;
       case expK:
            break;
       case returnK:
            break;
       case sequenceK:
            onlylocalsfirst = 
                weedSTATEMENTlocals(s->val.sequenceS.first,localsallowed);
            onlylocalssecond = 
                weedSTATEMENTlocals(s->val.sequenceS.second,onlylocalsfirst);
            return onlylocalsfirst && onlylocalssecond;
            break;
       case ifK:
            (void)weedSTATEMENTlocals(s->val.ifS.body,0);
            break;
       case ifelseK:
            (void)weedSTATEMENTlocals(s->val.ifelseS.thenpart,0);
            (void)weedSTATEMENTlocals(s->val.ifelseS.elsepart,0);
            break;
       case whileK:
            (void)weedSTATEMENTlocals(s->val.whileS.body,0);
            break;
       case blockK:
            (void)weedSTATEMENTlocals(s->val.blockS.body,1);
            break;
       case superconsK:
            return 1;
            break;
     }
  }
  return 0;
}

void weedSTATEMENTmain(STATEMENT *s)
{ if (s!=NULL) {
     switch (s->kind) {
       case skipK:
            break;
       case localK:
            break;
       case expK:
            weedEXPmain(s->val.expS);
            break;
       case returnK:
            break;
       case sequenceK:
            weedSTATEMENTmain(s->val.sequenceS.first);
            weedSTATEMENTmain(s->val.sequenceS.second);
            break;
       case ifK:
            weedEXPmain(s->val.ifS.condition);
            weedSTATEMENTmain(s->val.ifS.body);
            break;
       case ifelseK:
            weedEXPmain(s->val.ifelseS.condition);
            weedSTATEMENTmain(s->val.ifelseS.thenpart);
            weedSTATEMENTmain(s->val.ifelseS.elsepart);
            break;
       case whileK:
            weedEXPmain(s->val.whileS.condition);
            weedSTATEMENTmain(s->val.whileS.body);
            break;
       case blockK:
            weedSTATEMENTmain(s->val.blockS.body);
            break;
       case superconsK:
            weedARGUMENTmain(s->val.superconsS.args);
            break;
     }
  }
}

void weedEXPmain(EXP *e)
{ switch (e->kind) {
    case idK:
         break;
    case assignK:
         weedEXPmain(e->val.assignE.right);
         break;
    case orK:
         weedEXPmain(e->val.orE.left);
         weedEXPmain(e->val.orE.right);
         break;
    case andK:
         weedEXPmain(e->val.andE.left);
         weedEXPmain(e->val.andE.right);
         break;
    case eqK:
         weedEXPmain(e->val.eqE.left);
         weedEXPmain(e->val.eqE.right);
         break;
    case ltK:
         weedEXPmain(e->val.ltE.left);
         weedEXPmain(e->val.ltE.right);
         break;
    case gtK:
         weedEXPmain(e->val.gtE.left);
         weedEXPmain(e->val.gtE.right);
         break;
    case leqK:
         weedEXPmain(e->val.leqE.left);
         weedEXPmain(e->val.leqE.right);
         break;
    case geqK:
         weedEXPmain(e->val.geqE.left);
         weedEXPmain(e->val.geqE.right);
         break;
    case neqK:
         weedEXPmain(e->val.neqE.left);
         weedEXPmain(e->val.neqE.right);
         break;
    case instanceofK:
         weedEXPmain(e->val.instanceofE.left);
         break;
    case plusK:
         weedEXPmain(e->val.plusE.left);
         weedEXPmain(e->val.plusE.right);
         break;
    case minusK:
         weedEXPmain(e->val.minusE.left);
         weedEXPmain(e->val.minusE.right);
         break;
    case timesK:
         weedEXPmain(e->val.timesE.left);
         weedEXPmain(e->val.timesE.right);
         break;
    case divK:
         weedEXPmain(e->val.divE.left);
         weedEXPmain(e->val.divE.right);
         break;
    case modK:
         weedEXPmain(e->val.modE.left);
         weedEXPmain(e->val.modE.right);
         break;
    case notK:
         weedEXPmain(e->val.notE.not);
         break;
    case uminusK:
         weedEXPmain(e->val.uminusE);
         break;
    case thisK:
         reportError("this not allowed in main method",e->lineno);
         break;
    case newK:
         weedARGUMENTmain(e->val.newE.args);
         break;
    case invokeK:
         weedRECEIVERmain(e->val.invokeE.receiver);
         weedARGUMENTmain(e->val.invokeE.args);
         break;
    case intconstK:
         break;
    case boolconstK:
         break;
    case charconstK:
         break;
    case stringconstK:
         break;
    case nullK:
         break;
    case castK:
         weedEXPmain(e->val.castE.right);
         break;
    case charcastK:
         weedEXPmain(e->val.charcastE);
         break;
  }
}

void weedRECEIVERmain(RECEIVER *r)
{ switch (r->kind) {
    case objectK:
         weedEXPmain(r->objectR);
         break;
    case superK:
         reportError("super not allowed in main method",r->lineno);
         break;
  }
}

void weedARGUMENTmain(ARGUMENT *a)
{ if (a!=NULL) {
     weedARGUMENTmain(a->next);
     weedEXPmain(a->exp);
  }
}

int weedSTATEMENTreturns(STATEMENT *s)
{ if (s!=NULL) {
     switch (s->kind) {
       case skipK:
            return 0;
            break;
       case localK:
            return 0;
            break;
       case expK:
            return 0;
            break;
       case returnK:
            return 1;
            break;
       case sequenceK:
            return weedSTATEMENTreturns(s->val.sequenceS.second);
            break;
       case ifK:
            return 0;
            break;
       case ifelseK:
            return weedSTATEMENTreturns(s->val.ifelseS.thenpart) &&
                   weedSTATEMENTreturns(s->val.ifelseS.elsepart);
            break;
       case whileK:
            return 0;
            break;
       case blockK:
            return weedSTATEMENTreturns(s->val.blockS.body);
            break;
       case superconsK:
            return 0;
            break;
     }
  }
  return 0;
}

