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
#include "memory.h"
#include "error.h"
#include "defasn.h"

extern char *currentfile;

ASNSET *setUniversal()
{ ASNSET *a;
  a = NEW(ASNSET);
  a->kind = universalK;
  return a;
}

int setMember(ASNSET *s,LOCAL *l)
{ if (s==NULL) return 0;
  if (s->kind==universalK) return 1;
  if (s->kind==singleK && s->val.singleS==l) return 1;
  if (s->kind==intersectK && setMember(s->val.intersectS.first,l) 
                          && setMember(s->val.intersectS.second,l)) return 1;
  if (s->kind==unionK && (setMember(s->val.unionS.first,l) ||
                          setMember(s->val.unionS.second,l))) return 1;
  return setMember(s->next,l);
}

ASNSET *setInsert(ASNSET *s,LOCAL *l)
{ ASNSET *a;
  if (setMember(s,l)) return s;
  a = NEW(ASNSET);
  a->kind = singleK;
  a->val.singleS = l;
  a->next = s;
  return a;
}

ASNSET *setIntersect(ASNSET *l1, ASNSET *l2)
{ ASNSET *a;
  a = NEW(ASNSET);
  a->kind = intersectK;
  a->val.intersectS.first = l1;
  a->val.intersectS.second = l2;
  a->next = NULL;
  return a;
}

ASNSET *setUnion(ASNSET *l1, ASNSET *l2)
{ ASNSET *a;
  a = NEW(ASNSET);
  a->kind = unionK;
  a->val.unionS.first = l1;
  a->val.unionS.second = l2;
  a->next = NULL;
  return a;
}

void defasnPROGRAM(PROGRAM *p) 
{ if (p!=NULL) {
     defasnPROGRAM(p->next);
     currentfile = p->name;
     defasnCLASSFILE(p->classfile);
  }
}

void defasnCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
     defasnCLASSFILE(c->next);
     defasnCLASS(c->class);
  }
}

void defasnCLASS(CLASS *c)
{ defasnCONSTRUCTOR(c->constructors);
  defasnMETHOD(c->methods);
}

void defasnCONSTRUCTOR(CONSTRUCTOR *c)
{ if (c!=NULL) {
     defasnCONSTRUCTOR(c->next);
     (void)defasnSTATEMENT(c->statements,NULL);
  }
}

void defasnMETHOD(METHOD *m)
{ if (m!=NULL) {
     defasnMETHOD(m->next);
     (void)defasnSTATEMENT(m->statements,NULL);
  }
}

ASNSET *defasnSTATEMENT(STATEMENT *s, ASNSET *before)
{ if (s!=NULL) {
     switch (s->kind) {
       case skipK:
            return before;
       case localK:
            return before;
       case expK:
            return defasnEXP(s->val.expS,before);
       case returnK:
            if (s->val.returnS!=NULL) (void)defasnEXP(s->val.returnS,before);
            return setUniversal();
       case sequenceK:
            return defasnSTATEMENT(s->val.sequenceS.second,
                      defasnSTATEMENT(s->val.sequenceS.first,before)
                   );
       case ifK:
            return setIntersect(
                      defasnEXPassume(s->val.ifS.condition,before,0),
                      defasnSTATEMENT(s->val.ifS.body,
                         defasnEXPassume(s->val.ifS.condition,before,1)
                      )
                   );
       case ifelseK:
            return setIntersect(
                      defasnSTATEMENT(s->val.ifelseS.thenpart,
                         defasnEXPassume(s->val.ifelseS.condition,before,1)
                      ),
                      defasnSTATEMENT(s->val.ifelseS.elsepart,
                         defasnEXPassume(s->val.ifelseS.condition,before,0)
                      )
                   );
       case whileK:
            return setIntersect(
                      defasnEXPassume(s->val.whileS.condition,before,0),
                      defasnSTATEMENT(s->val.whileS.body,
                         defasnEXPassume(s->val.whileS.condition,before,1)
                      )
                   );
       case blockK:
            return defasnSTATEMENT(s->val.blockS.body,before);
       case superconsK:
            return defasnARGUMENT(s->val.superconsS.args,before);
     }
  }
  return before;
}

ASNSET *defasnEXPassume(EXP *e, ASNSET *before, int assume)
{ switch(e->kind) {
    case idK:
         if (e->val.idE.idsym->kind==localSym &&
             !setMember(before,e->val.idE.idsym->val.localS)) {
             reportStrError("variable %s may not have been initialized",
                            e->val.idE.name,e->lineno);
         }
         return before;
    case assignK:
         switch (e->val.assignE.leftsym->kind) {
           case localSym:
                return setInsert(
                          defasnEXPassume(e->val.assignE.right,before,assume),
                          e->val.assignE.leftsym->val.localS
                       );
           case formalSym:
           case fieldSym:
           case classSym:
           case methodSym:
                return defasnEXPassume(e->val.assignE.right,before,assume);
         }
    case orK:
         if (assume) {
            return setIntersect(
                      defasnEXPassume(e->val.orE.left,before,1),
                      defasnEXPassume(e->val.orE.right,
                         defasnEXPassume(e->val.orE.left,before,0),1
                      )
                   );
         } else {
            return setUnion(
                      defasnEXPassume(e->val.orE.left,before,0),
                      defasnEXPassume(e->val.orE.right,
                         defasnEXPassume(e->val.orE.left,before,0),0
                      )
                   );
         }
    case andK:
         if (assume) {
            return setUnion(
                      defasnEXPassume(e->val.orE.left,before,1),
                      defasnEXPassume(e->val.orE.right,
                         defasnEXPassume(e->val.orE.left,before,1),1
                      )
                   );
         } else {
            return setIntersect(
                      defasnEXPassume(e->val.orE.left,before,0),
                      defasnEXPassume(e->val.orE.right,
                         defasnEXPassume(e->val.orE.left,before,1),0
                      )
                   );
         }
    case notK:
         return defasnEXPassume(e->val.notE.not,before,!assume);
    case boolconstK:
         if (e->val.boolconstE!=assume) return setUniversal();
         else return before;
    default: 
         return defasnEXP(e,before);
  }
}

ASNSET *defasnEXP(EXP *e, ASNSET *before)
{ switch(e->kind) {
    case idK:
         if (e->val.idE.idsym->kind==localSym &&
             !setMember(before,e->val.idE.idsym->val.localS)) {
             reportStrError("variable %s may not have been initialized",
                            e->val.idE.name,e->lineno);
         }
         return before;
    case assignK:
         switch (e->val.assignE.leftsym->kind) {
           case localSym:
                return setInsert(
                          defasnEXP(e->val.assignE.right,before),
                          e->val.assignE.leftsym->val.localS
                       );
           case formalSym:
           case fieldSym:
           case classSym:
           case methodSym:
                return defasnEXP(e->val.assignE.right,before);
         }
    case plusK:
         return defasnEXP(e->val.plusE.right,
                  defasnEXP(e->val.plusE.left,before)
                );
    case minusK:
         return defasnEXP(e->val.minusE.right,
                  defasnEXP(e->val.minusE.left,before)
                );
    case timesK:
         return defasnEXP(e->val.timesE.right,
                  defasnEXP(e->val.timesE.left,before)
                );
    case divK:
         return defasnEXP(e->val.divE.right,
                  defasnEXP(e->val.divE.left,before)
                );
    case modK:
         return defasnEXP(e->val.modE.right,
                  defasnEXP(e->val.modE.left,before)
                );
    case eqK:
         return defasnEXP(e->val.eqE.right,
                  defasnEXP(e->val.eqE.left,before)
                );
    case ltK:
         return defasnEXP(e->val.ltE.right,
                  defasnEXP(e->val.ltE.left,before)
                );
    case gtK:
         return defasnEXP(e->val.gtE.right,
                  defasnEXP(e->val.gtE.left,before)
                );
    case geqK:
         return defasnEXP(e->val.geqE.right,
                  defasnEXP(e->val.geqE.left,before)
                );
    case leqK:
         return defasnEXP(e->val.leqE.right,
                  defasnEXP(e->val.leqE.left,before)
                );
    case neqK:
         return defasnEXP(e->val.neqE.right,
                  defasnEXP(e->val.neqE.left,before)
                );
    case uminusK:
         return defasnEXP(e->val.uminusE,before);
    case thisK:
         return before;
    case newK:
         return defasnARGUMENT(e->val.newE.args,before);
    case instanceofK:
         return defasnEXP(e->val.instanceofE.left,before);
    case invokeK:
         return defasnARGUMENT(e->val.newE.args,
                  defasnRECEIVER(e->val.invokeE.receiver,before)
                );
    case intconstK:
         return before;
    case charconstK:
         return before;
    case stringconstK:
         return before;
    case nullK:
         return before;
    case castK:
         return defasnEXP(e->val.castE.right,before);
    case charcastK:
         return defasnEXP(e->val.charcastE,before);
    default: 
         if (e->type->kind==boolK)
            return setIntersect(defasnEXPassume(e,before,1),defasnEXPassume(e,before,0));
         else 
            return before;
  }
}

ASNSET *defasnRECEIVER(RECEIVER *r, ASNSET *before)
{ switch(r->kind) {
    case objectK:
         return defasnEXP(r->objectR,before);
    case superK:
         return before;
  }
  return before;
}

ASNSET *defasnARGUMENT(ARGUMENT *a, ASNSET *before)
{ if (a!=NULL) 
     return defasnEXP(a->exp,defasnARGUMENT(a->next,before));
  else 
     return before;
}
