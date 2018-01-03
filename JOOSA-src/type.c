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
#include "error.h"
#include "symbol.h"
#include "type.h"

extern char *currentfile;

TYPE *polynullTYPE, *intTYPE, *boolTYPE, *charTYPE, *stringTYPE;

TYPE *classTYPE(CLASS *c)
{ TYPE *t;
  t = NEW(TYPE);
  t->kind = refK;
  t->name = c->name;
  t->class = c;
  return t;
}

void initTypes()
{ SYMBOL *s;
  polynullTYPE = NEW(TYPE);
  polynullTYPE->kind = polynullK;
  intTYPE = NEW(TYPE);
  intTYPE->kind = intK;
  boolTYPE = NEW(TYPE);
  boolTYPE->kind = boolK;
  charTYPE = NEW(TYPE);
  charTYPE->kind = charK;
  s = getSymbol(classlib,"String");
  if (s==NULL) {
     reportGlobalError("class String not found");
     noErrors();
  }
  stringTYPE = NEW(TYPE);
  stringTYPE->kind = refK;
  stringTYPE->name = "String";
  stringTYPE->class = s->val.classS;
}

int equalTYPE(TYPE *s, TYPE *t)
{ if (s->kind!=t->kind) return 0;
  if (s->kind==refK) {
     return strcmp(s->name,t->name)==0;
  }
  return 1;
}

int integerTYPE(TYPE *t)
{ return t->kind==intK || t->kind==charK;
}

int assignTYPE(TYPE *s, TYPE *t)
{ if (s->kind==refK && t->kind==polynullK) return 1;
  if (s->kind==intK && t->kind==charK) return 1;
  if (s->kind!=t->kind) return 0;
  if (s->kind==refK) return subClass(t->class,s->class);
  return 1;
}

int checkBOOL(TYPE *t, int lineno)
{ if (t->kind!=boolK) {
     reportError("boolean type expected",lineno);
     return 0;
  }
  return 1;
}

int checkCHAR(TYPE *t, int lineno)
{ if (t->kind!=charK) {
     reportError("char type expected",lineno);
     return 0;
  }
  return 1;
}

int checkINT(TYPE *t, int lineno)
{ if (t->kind!=intK && t->kind!=charK) {
     reportError("int type expected",lineno);
     return 0;
  }
  return 1;
}

int equalFORMAL(FORMAL *f, FORMAL *g)
{ if (f==NULL || g==NULL) return f==NULL && g==NULL;
  return equalTYPE(f->type,g->type) && equalFORMAL(f->next,g->next);
}

void typePROGRAM(PROGRAM *p)
{ initTypes();
  typeHierarchyPROGRAM(p);
  typeImplementationPROGRAM(p);
}

void typeHierarchyPROGRAM(PROGRAM *p)
{ if (p!=NULL) {
     typeHierarchyPROGRAM(p->next);
     currentfile = p->name;
     typeHierarchyCLASSFILE(p->classfile);
  }
}

void typeHierarchyCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
     typeHierarchyCLASSFILE(c->next);
     typeHierarchyCLASS(c->class);
  }
}

void typeHierarchyCLASS(CLASS *c)
{ if (subClass(c->parent,c)) {
     reportError("cyclic inheritance",c->lineno);
  }
  if (c->parent!=NULL) {
     if (c->parent->modifier==finalMod) {
        reportStrError("extension of final %s class",c->parentname,c->lineno);
     }
  }
  typeHierarchyFIELD(c->fields,c);
  typeHierarchyMETHOD(c->methods,c);
}

void typeHierarchyFIELD(FIELD *f, CLASS *this)
{ SYMBOL *s;
  if (f!=NULL) {
     typeHierarchyFIELD(f->next,this);
     s = lookupHierarchy(f->name,this->parent);
     if (s!=NULL) {
        reportStrError("illegal overriding of field %s",f->name,f->lineno);
     }
  }
}

void typeHierarchyMETHOD(METHOD *m, CLASS *this)
{ SYMBOL *s;
  if (m!=NULL) {
     typeHierarchyMETHOD(m->next,this);
     s = lookupHierarchy(m->name,this->parent);
     if (s!=NULL) {
        if (s->kind!=methodSym) {
           reportStrError("illegal overriding of method %s",m->name,m->lineno);
        } else {
           if (s->val.methodS->modifier==finalMod) {
              reportStrError("illegal overriding of final method %s",
                             m->name,m->lineno);
           } else {
              if (!equalFORMAL(m->formals,s->val.methodS->formals) ||
                  !equalTYPE(m->returntype,s->val.methodS->returntype)) {
                 reportStrError("overriden method %s must have same signature",
                                 m->name, m->lineno);
              }
           }
        }
     }
  }
}

void typeImplementationPROGRAM(PROGRAM *p)
{ if (p!=NULL) {
     typeImplementationPROGRAM(p->next);
     currentfile = p->name;
     typeImplementationCLASSFILE(p->classfile);
  }
}

void typeImplementationCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
     typeImplementationCLASSFILE(c->next);
     typeImplementationCLASS(c->class);
  }
}

int memberCONSTRUCTOR(CONSTRUCTOR *c, CONSTRUCTOR *l)
{ if (l==NULL) return 0;
  if (equalFORMAL(c->formals,l->formals)) return 1;
  return memberCONSTRUCTOR(c,l->next);
}

void uniqueCONSTRUCTOR(CONSTRUCTOR *c)
{ if (c!=NULL) {
     uniqueCONSTRUCTOR(c->next);
     if (memberCONSTRUCTOR(c,c->next)) reportError("duplicate constructor",c->lineno);
  }
}

void typeImplementationCLASS(CLASS *c)
{ typeImplementationCONSTRUCTOR(c->constructors,c);
  uniqueCONSTRUCTOR(c->constructors);
  typeImplementationMETHOD(c->methods,c);
}

void typeImplementationCONSTRUCTOR(CONSTRUCTOR *c, CLASS *this)
{ if (c!=NULL) {
     typeImplementationCONSTRUCTOR(c->next,this);
     typeImplementationSTATEMENT(c->statements,this,makeTYPEvoid());
  }
}

void typeImplementationMETHOD(METHOD *m, CLASS *this)
{ if (m!=NULL) {
     typeImplementationMETHOD(m->next,this);
     typeImplementationSTATEMENT(m->statements,this,m->returntype);
  }
}

TYPE *typePlus(EXP *left, EXP *right, int lineno)
{ if (integerTYPE(left->type) && integerTYPE(right->type)) {
     return intTYPE;
  }
  if (!equalTYPE(left->type,stringTYPE) && !equalTYPE(right->type,stringTYPE)) {
     reportError("arguments for + have wrong types",lineno);
  }
  left->tostring = 1;
  right->tostring = 1;
  return stringTYPE;
}

int applicableFORMALARGUMENT(FORMAL *f, ARGUMENT *a)
{ if (f==NULL || a==NULL) return (f==NULL && a==NULL);
  if (!assignTYPE(f->type,a->exp->type)) return 0;
  return applicableFORMALARGUMENT(f->next,a->next);
}

CONSTRUCTOR *applicableCONSTRUCTOR(CONSTRUCTOR *c, ARGUMENT *a)
{ if (c==NULL) return NULL;
  if (applicableFORMALARGUMENT(c->formals,a)) {
     return makeCONSTRUCTOR(c->name,c->formals,c->statements,
                            applicableCONSTRUCTOR(c->next,a));
  } else {
     return applicableCONSTRUCTOR(c->next,a);
  }
}

int morespecificFORMAL(FORMAL *f, FORMAL *g)
{ if (f==NULL || g==NULL) return (f==NULL && g==NULL);
  if (!assignTYPE(g->type,f->type)) return 0;
  return morespecificFORMAL(f->next,g->next);
}

int maxspecificFORMALCONSTRUCTOR(FORMAL *f, CONSTRUCTOR *d)
{ if (d==NULL) return 1;
  if (!morespecificFORMAL(f,d->formals)) return 0;
  return maxspecificFORMALCONSTRUCTOR(f,d->next);
}

CONSTRUCTOR *maxspecificCONSTRUCTOR(CONSTRUCTOR *c, CONSTRUCTOR *d)
{ if (c==NULL) return NULL;
  if (maxspecificFORMALCONSTRUCTOR(c->formals,d)) {
     return makeCONSTRUCTOR(c->name,c->formals,c->statements,
                            maxspecificCONSTRUCTOR(c->next,d));
  } else {
     return maxspecificCONSTRUCTOR(c->next,d);
  }
}

CONSTRUCTOR *selectCONSTRUCTOR(CONSTRUCTOR *c, ARGUMENT *a, int lineno)
{ CONSTRUCTOR *applicable;
  applicable = applicableCONSTRUCTOR(c,a);
  if (applicable==NULL) {
     reportError("no matching constructor",lineno);
     return NULL;
  } else {
     CONSTRUCTOR *maxspecific;
     maxspecific = maxspecificCONSTRUCTOR(applicable,applicable);
     if (maxspecific==NULL || maxspecific->next!=NULL) 
        reportError("ambiguous constructor",lineno);
     return maxspecific;
  }
}

void typeImplementationSTATEMENT(STATEMENT *s, CLASS *this, TYPE *returntype)
{ if (s!=NULL) {
     switch (s->kind) {
       case skipK:
            break;
       case localK:
            break;
       case expK:
            typeImplementationEXP(s->val.expS,this);
            break;
       case returnK:
            if (s->val.returnS!=NULL) {
               typeImplementationEXP(s->val.returnS,this);
            }
            if (returntype->kind==voidK && s->val.returnS!=NULL) {
               reportError("return value not allowed",s->lineno);
            }
            if (returntype->kind!=voidK && s->val.returnS==NULL) {
               reportError("return value expected",s->lineno);
            }
            if (returntype->kind!=voidK && s->val.returnS!=NULL) {
               if (!assignTYPE(returntype,s->val.returnS->type)) {
                  reportError("illegal type of expression",s->lineno);
               }
            }
            break;
       case sequenceK:
            typeImplementationSTATEMENT(s->val.sequenceS.first,this,returntype);
            typeImplementationSTATEMENT(s->val.sequenceS.second,this,returntype);
            break;
       case ifK:
            typeImplementationEXP(s->val.ifS.condition,this);
            checkBOOL(s->val.ifS.condition->type,s->lineno);
            typeImplementationSTATEMENT(s->val.ifS.body,this,returntype);
            break;
       case ifelseK:
            typeImplementationEXP(s->val.ifelseS.condition,this);
            checkBOOL(s->val.ifelseS.condition->type,s->lineno);
            typeImplementationSTATEMENT(s->val.ifelseS.thenpart,this,returntype);
            typeImplementationSTATEMENT(s->val.ifelseS.elsepart,this,returntype);
            break;
       case whileK:
            typeImplementationEXP(s->val.whileS.condition,this);
            checkBOOL(s->val.whileS.condition->type,s->lineno);
            typeImplementationSTATEMENT(s->val.whileS.body,this,returntype);
            break;
       case blockK:
            typeImplementationSTATEMENT(s->val.blockS.body,this,returntype);
            break;
       case superconsK:
            typeImplementationARGUMENT(s->val.superconsS.args,this);
            s->val.superconsS.constructor = selectCONSTRUCTOR(this->parent->constructors,
                                                              s->val.superconsS.args,
                                                              s->lineno);
            break;
     }
  }
}

TYPE *typeVar(SYMBOL *s)
{ switch(s->kind) {
    case fieldSym: 
         return s->val.fieldS->type;
         break;
    case formalSym:
         return s->val.formalS->type;
         break;
    case localSym:
         return s->val.localS->type;
         break;
    case classSym:
    case methodSym:
         break;
  }
  return NULL;
}

void typeImplementationEXP(EXP *e, CLASS *this)
{ SYMBOL *s;
  TYPE *t;
  switch (e->kind) {
    case idK:
         e->type = typeVar(e->val.idE.idsym);
         break;
    case assignK:
         e->type = typeVar(e->val.assignE.leftsym);
         typeImplementationEXP(e->val.assignE.right,this);
         if (!assignTYPE(e->type,e->val.assignE.right->type)) {
            reportError("illegal assignment",e->lineno);
         }
         break;
    case orK:
         typeImplementationEXP(e->val.orE.left,this);
         typeImplementationEXP(e->val.orE.right,this);
         checkBOOL(e->val.orE.left->type,e->lineno);
         checkBOOL(e->val.orE.right->type,e->lineno);
         e->type = boolTYPE;
         break;
    case andK:
         typeImplementationEXP(e->val.andE.left,this);
         typeImplementationEXP(e->val.andE.right,this);
         checkBOOL(e->val.andE.left->type,e->lineno);
         checkBOOL(e->val.andE.right->type,e->lineno);
         e->type = boolTYPE;
         break;
    case eqK:
         typeImplementationEXP(e->val.eqE.left,this);
         typeImplementationEXP(e->val.eqE.right,this);
         if (!assignTYPE(e->val.eqE.left->type,e->val.eqE.right->type) &&
             !assignTYPE(e->val.eqE.right->type,e->val.eqE.left->type)) {
            reportError("arguments for = have wrong types",e->lineno);
         }
         e->type = boolTYPE;
         break;
    case ltK:
         typeImplementationEXP(e->val.ltE.left,this);
         typeImplementationEXP(e->val.ltE.right,this);
         checkINT(e->val.ltE.left->type,e->lineno);
         checkINT(e->val.ltE.right->type,e->lineno);
         e->type = boolTYPE;
         break;
    case gtK:
         typeImplementationEXP(e->val.gtE.left,this);
         typeImplementationEXP(e->val.gtE.right,this);
         checkINT(e->val.gtE.left->type,e->lineno);
         checkINT(e->val.gtE.right->type,e->lineno);
         e->type = boolTYPE;
         break;
    case leqK:
         typeImplementationEXP(e->val.leqE.left,this);
         typeImplementationEXP(e->val.leqE.right,this);
         checkINT(e->val.leqE.left->type,e->lineno);
         checkINT(e->val.leqE.right->type,e->lineno);
         e->type = boolTYPE;
         break;
    case geqK:
         typeImplementationEXP(e->val.geqE.left,this);
         typeImplementationEXP(e->val.geqE.right,this);
         checkINT(e->val.geqE.left->type,e->lineno);
         checkINT(e->val.geqE.right->type,e->lineno);
         e->type = boolTYPE;
         break;
    case neqK:
         typeImplementationEXP(e->val.neqE.left,this);
         typeImplementationEXP(e->val.neqE.right,this);
         if (!assignTYPE(e->val.neqE.left->type,e->val.neqE.right->type) &&
             !assignTYPE(e->val.neqE.right->type,e->val.neqE.left->type)) {
            reportError("arguments for != have wrong types",e->lineno);
         }
         e->type = boolTYPE;
         break;
    case instanceofK:
         typeImplementationEXP(e->val.instanceofE.left,this);
         if (e->val.instanceofE.left->type->kind!=refK) {
            reportError("class reference expected",e->lineno);
         } 
         if (!subClass(e->val.instanceofE.left->type->class,
                       e->val.instanceofE.class) &&
             !subClass(e->val.instanceofE.class,
                       e->val.instanceofE.left->type->class)) {
            reportError("instanceof will always fail",e->lineno);
         }
         e->type = boolTYPE;
         break;
    case plusK:
         typeImplementationEXP(e->val.plusE.left,this);
         typeImplementationEXP(e->val.plusE.right,this);
         e->type = typePlus(e->val.plusE.left,e->val.plusE.right,e->lineno);
         break;
    case minusK:
         typeImplementationEXP(e->val.minusE.left,this);
         typeImplementationEXP(e->val.minusE.right,this);
         checkINT(e->val.minusE.left->type,e->lineno);
         checkINT(e->val.minusE.right->type,e->lineno);
         e->type = intTYPE;
         break;
    case timesK:
         typeImplementationEXP(e->val.timesE.left,this);
         typeImplementationEXP(e->val.timesE.right,this);
         checkINT(e->val.timesE.left->type,e->lineno);
         checkINT(e->val.timesE.right->type,e->lineno);
         e->type = intTYPE;
         break;
    case divK:
         typeImplementationEXP(e->val.divE.left,this);
         typeImplementationEXP(e->val.divE.right,this);
         checkINT(e->val.divE.left->type,e->lineno);
         checkINT(e->val.divE.right->type,e->lineno);
         e->type = intTYPE;
         break;
    case modK:
         typeImplementationEXP(e->val.modE.left,this);
         typeImplementationEXP(e->val.modE.right,this);
         checkINT(e->val.modE.left->type,e->lineno);
         checkINT(e->val.modE.right->type,e->lineno);
         e->type = intTYPE;
         break;
    case notK:
         typeImplementationEXP(e->val.notE.not,this);
         checkBOOL(e->val.notE.not->type,e->lineno);
         e->type = boolTYPE;
         break;
    case uminusK:
         typeImplementationEXP(e->val.uminusE,this);
         checkINT(e->val.uminusE->type,e->lineno);
         e->type = intTYPE;
         break;
    case thisK:
         if (this==NULL) {
            reportError("'this' not allowed here",e->lineno);
         }
         e->type = classTYPE(this);
         break;
    case newK:
         if (e->val.newE.class->modifier==abstractMod) {
             reportStrError("illegal abstract constructor %s",
                             e->val.newE.class->name,e->lineno);
         }
         typeImplementationARGUMENT(e->val.newE.args,this);
         e->val.newE.constructor = selectCONSTRUCTOR(e->val.newE.class->constructors,
                                                     e->val.newE.args,
                                                     e->lineno);
         e->type = classTYPE(e->val.newE.class);
         break;
    case invokeK:
         t = typeImplementationRECEIVER(e->val.invokeE.receiver,this);
         typeImplementationARGUMENT(e->val.invokeE.args,this);
         if (t->kind!=refK) {
            reportError("receiver must be an object",e->lineno);
            e->type = polynullTYPE;
         } else {
            s = lookupHierarchy(e->val.invokeE.name,t->class);
            if (s==NULL || s->kind!=methodSym) {
               reportStrError("no such method called %s",
                                e->val.invokeE.name,e->lineno);
               e->type = polynullTYPE;
            } else {
               e->val.invokeE.method = s->val.methodS;
               if (s->val.methodS->modifier==staticMod) {
                  reportStrError("static method %s may not be invoked",
                                 e->val.invokeE.name,e->lineno);
               }
               typeImplementationFORMALARGUMENT(s->val.methodS->formals,
                                                e->val.invokeE.args,
                                                e->lineno);
               e->type = s->val.methodS->returntype;
            }
         }
         break;
    case intconstK:
         e->type = intTYPE;
         break;
    case boolconstK:
         e->type = boolTYPE;
         break;
    case charconstK:
         e->type = charTYPE;
         break;
    case stringconstK:
         e->type = stringTYPE;
         break;
    case nullK:
         e->type = polynullTYPE;
         break;
    case castK:
         typeImplementationEXP(e->val.castE.right,this);
         e->type = makeTYPEextref(e->val.castE.left,e->val.castE.class);
         if (e->val.castE.right->type->kind!=refK &&
             e->val.castE.right->type->kind!=polynullK) {
            reportError("class reference expected",e->lineno);
         } else {
            if (e->val.castE.right->type->kind==refK &&
                !subClass(e->val.castE.class,
                          e->val.castE.right->type->class) &&
                !subClass(e->val.castE.right->type->class,
                          e->val.castE.class)) {
               reportError("cast will always fail",e->lineno);
            }
         }
         break;
    case charcastK:
         typeImplementationEXP(e->val.charcastE,this);
         checkINT(e->val.charcastE->type,e->lineno);
         e->type = charTYPE;
         break;
  }
}

void typeImplementationARGUMENT(ARGUMENT *a, CLASS *this)
{ if (a!=NULL) {
     typeImplementationARGUMENT(a->next,this);
     typeImplementationEXP(a->exp,this);
  }
}

TYPE *typeImplementationRECEIVER(RECEIVER *r, CLASS *this)
{ switch(r->kind) {
    case objectK:
         typeImplementationEXP(r->objectR,this);
         return r->objectR->type;
         break;
    case superK:
         if (this->parent==NULL) {
            reportError("super not allowed here",r->lineno);
         }
         return classTYPE(this->parent);
         break;
  }
  return NULL;
}

void typeImplementationFORMALARGUMENT(FORMAL *f, ARGUMENT *a, int lineno)
{ if (f==NULL && a!=NULL) {
     reportError("too many arguments",a->exp->lineno);
     return;
  }
  if (f!=NULL && a==NULL) {
     reportError("too few arguments",lineno);
     return;
  }
  if (f!=NULL && a!=NULL) {
     typeImplementationFORMALARGUMENT(f->next,a->next,lineno);
     if (!assignTYPE(f->type,a->exp->type)) {
        reportError("argument has wrong type",a->exp->lineno);
     }
  }
}
