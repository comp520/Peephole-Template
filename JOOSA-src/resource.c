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
#include "resource.h"

int label;

int nextlabel()
{ return label++;
}

int offset, localslimit;

int nextoffset()
{ offset++;
  if (offset > localslimit) localslimit = offset;
  return offset;
}

void resPROGRAM(PROGRAM *p)
{ if (p!=NULL) {
     resPROGRAM(p->next);
     resCLASSFILE(p->classfile);
  }
}

void resCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
     resCLASSFILE(c->next);
     resCLASS(c->class);
  }
}

void resCLASS(CLASS *c)
{ resCONSTRUCTOR(c->constructors);
  resMETHOD(c->methods);
}

void resCONSTRUCTOR(CONSTRUCTOR *c)
{ if (c!=NULL) {
     resCONSTRUCTOR(c->next);
     offset = 0;
     localslimit = 0;
     label = 0;
     resFORMAL(c->formals);
     resSTATEMENT(c->statements);
     c->labelcount = label;
     c->localslimit = localslimit+1;
  }
}

void resMETHOD(METHOD *m)
{ if (m!=NULL) {
     resMETHOD(m->next);
     offset = 0;
     localslimit = 0;
     label = 0;
     resFORMAL(m->formals);
     resSTATEMENT(m->statements);
     m->labelcount = label;
     m->localslimit = localslimit+1;
  }
}

void resFORMAL(FORMAL *f)
{ if (f!=NULL) {
     resFORMAL(f->next);
     f->offset = nextoffset();
  }
}

void resLOCAL(LOCAL *l)
{ if (l!=NULL) {
     resLOCAL(l->next);
     l->offset = nextoffset();
  }
}

void resSTATEMENT(STATEMENT *s)
{ int baseoffset;
  if (s!=NULL) {
     switch (s->kind) {
        case skipK:
             break;
        case localK:
             resLOCAL(s->val.localS);
             break;
        case expK:
             resEXP(s->val.expS);
             break;
        case returnK:
             if (s->val.returnS!=NULL) resEXP(s->val.returnS);
             break;
        case sequenceK:
             resSTATEMENT(s->val.sequenceS.first);
             resSTATEMENT(s->val.sequenceS.second);
             break;
        case ifK:
             s->val.ifS.stoplabel = nextlabel();
             resEXP(s->val.ifS.condition);
             resSTATEMENT(s->val.ifS.body);
             break;
        case ifelseK:
             s->val.ifelseS.elselabel = nextlabel();
             s->val.ifelseS.stoplabel = nextlabel();
             resEXP(s->val.ifelseS.condition);
             resSTATEMENT(s->val.ifelseS.thenpart);
             resSTATEMENT(s->val.ifelseS.elsepart);
             break;
        case whileK:
             s->val.whileS.startlabel = nextlabel();
             s->val.whileS.stoplabel = nextlabel();
             resEXP(s->val.whileS.condition);
             resSTATEMENT(s->val.whileS.body);
             break;
        case blockK:
             baseoffset = offset;
             resSTATEMENT(s->val.blockS.body);
             offset = baseoffset;
             break;
        case superconsK:
             resARGUMENT(s->val.superconsS.args);
             break;
     }
  }
}

void resEXP(EXP *e)
{ if (e->tostring) {
     e->nulllabel = nextlabel();
     e->stoplabel = nextlabel();
  }
  switch (e->kind) {
    case idK:
         break;
    case assignK:
         resEXP(e->val.assignE.right);
         break;
    case orK:
         e->val.orE.truelabel = nextlabel();
         resEXP(e->val.orE.left);
         resEXP(e->val.orE.right);
         break;
    case andK:
         e->val.andE.falselabel = nextlabel();
         resEXP(e->val.andE.left);
         resEXP(e->val.andE.right);
         break;
    case eqK:
         e->val.eqE.truelabel = nextlabel();
         e->val.eqE.stoplabel = nextlabel();
         resEXP(e->val.eqE.left);
         resEXP(e->val.eqE.right);
         break;
    case ltK:
         e->val.ltE.truelabel = nextlabel();
         e->val.ltE.stoplabel = nextlabel();
         resEXP(e->val.ltE.left);
         resEXP(e->val.ltE.right);
         break;
    case gtK:
         e->val.gtE.truelabel = nextlabel();
         e->val.gtE.stoplabel = nextlabel();
         resEXP(e->val.gtE.left);
         resEXP(e->val.gtE.right);
         break;
    case leqK:
         e->val.leqE.truelabel = nextlabel();
         e->val.leqE.stoplabel = nextlabel();
         resEXP(e->val.leqE.left);
         resEXP(e->val.leqE.right);
         break;
    case geqK:
         e->val.geqE.truelabel = nextlabel();
         e->val.geqE.stoplabel = nextlabel();
         resEXP(e->val.geqE.left);
         resEXP(e->val.geqE.right);
         break;
    case neqK:
         e->val.neqE.truelabel = nextlabel();
         e->val.neqE.stoplabel = nextlabel();
         resEXP(e->val.neqE.left);
         resEXP(e->val.neqE.right);
         break;
    case instanceofK:
         resEXP(e->val.instanceofE.left);
         break;
    case plusK:
         resEXP(e->val.plusE.left);
         resEXP(e->val.plusE.right);
         break;
    case minusK:
         resEXP(e->val.minusE.left);
         resEXP(e->val.minusE.right);
         break;
    case timesK:
         resEXP(e->val.timesE.left);
         resEXP(e->val.timesE.right);
         break;
    case divK:
         resEXP(e->val.divE.left);
         resEXP(e->val.divE.right);
         break;
    case modK:
         resEXP(e->val.modE.left);
         resEXP(e->val.modE.right);
         break;
    case notK:
         e->val.notE.truelabel = nextlabel();
         e->val.notE.stoplabel = nextlabel();
         resEXP(e->val.notE.not);
         break;
    case uminusK:
         resEXP(e->val.uminusE);
         break;
    case thisK:
         break;
    case newK:
         resARGUMENT(e->val.newE.args);
         break;
    case invokeK:
         resRECEIVER(e->val.invokeE.receiver);
         resARGUMENT(e->val.invokeE.args);
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
         resEXP(e->val.castE.right);
         break;
    case charcastK:
         resEXP(e->val.charcastE);
         break;
  } 
}

void resRECEIVER(RECEIVER *r)
{ switch (r->kind) {
    case objectK:
         resEXP(r->objectR);
         break;
    case superK:
         break;
  }
}

void resARGUMENT(ARGUMENT *a)
{ if (a!=NULL) {
     resARGUMENT(a->next);
     resEXP(a->exp);
  }
}
