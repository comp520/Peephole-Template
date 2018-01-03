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

extern char *currentfile;

int Hash(char *str)
{ unsigned int hash = 0;
  while (*str) hash = (hash << 1) + *str++; 
  return hash % HashSize;
}

SymbolTable *initSymbolTable()
{ SymbolTable *t;
  int i;
  t = NEW(SymbolTable);
  for (i=0; i < HashSize; i++) t->table[i] = NULL;
  t->next = NULL;
  return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s)
{ SymbolTable *t;
  t = initSymbolTable();
  t->next = s;
  return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  s = NEW(SYMBOL);
  s->name = name;
  s->kind = kind;
  s->next = t->table[i];
  t->table[i] = s;
  return s;
}
 
SYMBOL *getSymbol(SymbolTable *t, char *name)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  if (t->next==NULL) return NULL;
  return getSymbol(t->next,name);
}
 
int defSymbol(SymbolTable *t, char *name)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return 1;
  }
  return 0;
}

int subClass(CLASS *sub, CLASS *super)
{ if (sub==NULL) return 0;
  if (strcmp(sub->name,super->name)==0) return 1;
  if (sub->parent==NULL) return 0;
  return subClass(sub->parent,super);
}

SYMBOL *lookupHierarchy(char *name, CLASS *start)
{ SYMBOL *s;
  if (start==NULL) return NULL;
  s = getSymbol(start->localsym,name);
  if (s!=NULL) return s;
  if (start->parent==NULL) return NULL;
  return lookupHierarchy(name,start->parent);
}

CLASS *lookupHierarchyClass(char *name, CLASS *start)
{ SYMBOL *s;
  if (start==NULL) return NULL;
  s = getSymbol(start->localsym,name);
  if (s!=NULL) return start;
  if (start->parent==NULL) return NULL;
  return lookupHierarchyClass(name,start->parent);
}

void symPROGRAM(PROGRAM *p)
{ classlib = initSymbolTable();
  symInterfacePROGRAM(p,classlib);
  symInterfaceTypesPROGRAM(p,classlib);
  symImplementationPROGRAM(p);
}

void symInterfacePROGRAM(PROGRAM *p, SymbolTable *sym)
{ if (p!=NULL) {
     symInterfacePROGRAM(p->next,sym);
     currentfile = p->name;
     symInterfaceCLASSFILE(p->classfile,sym);
  }
}

void symInterfaceCLASSFILE(CLASSFILE *c, SymbolTable *sym)
{ if (c!=NULL) {
     symInterfaceCLASSFILE(c->next,sym);
     symInterfaceCLASS(c->class,sym);
  }
}

void symInterfaceCLASS(CLASS *c, SymbolTable *sym)
{ SYMBOL *s;
  if (defSymbol(sym,c->name)) {
     reportStrError("class name %s already defined",c->name,c->lineno);
  } else {
     s = putSymbol(sym,c->name,classSym);
     s->val.classS = c;
     c->localsym = initSymbolTable();
     symInterfaceFIELD(c->fields,c->localsym);
     symInterfaceCONSTRUCTOR(c->constructors,c->name,c->localsym);
     symInterfaceMETHOD(c->methods,c->localsym);
  }
}

void symInterfaceFIELD(FIELD *f, SymbolTable *sym)
{ SYMBOL *s;
  if (f!=NULL) {
     symInterfaceFIELD(f->next,sym);
     s = putSymbol(sym,f->name,fieldSym);
     s->val.fieldS = f;
  }
}

void symInterfaceCONSTRUCTOR(CONSTRUCTOR *c, char *classname, SymbolTable *sym)
{ if (c!=NULL) {
     symInterfaceCONSTRUCTOR(c->next,classname,sym);
     if (!strcmp(classname,c->name)==0) {
        reportStrError("constructor name %s different from class name",
                         c->name,c->lineno);
     }
  }
}

void symInterfaceMETHOD(METHOD *m, SymbolTable *sym)
{ SYMBOL *s;
  if (m!=NULL) {
     symInterfaceMETHOD(m->next,sym);
     if (defSymbol(sym,m->name)) {
        reportStrError("Redefinition of an identifier: method name %s already defined",m->name,m->lineno);
     } else {
        s = putSymbol(sym,m->name,methodSym);
        s->val.methodS = m;
     }
  }   
}

void symInterfaceTypesPROGRAM(PROGRAM *p, SymbolTable *sym)
{ if (p!=NULL) {
     symInterfaceTypesPROGRAM(p->next,sym);
     currentfile = p->name;
     symInterfaceTypesCLASSFILE(p->classfile,sym);
  }
}

void symInterfaceTypesCLASSFILE(CLASSFILE *c, SymbolTable *sym)
{ if (c!=NULL) {
     symInterfaceTypesCLASSFILE(c->next,sym);
     symInterfaceTypesCLASS(c->class,sym);
  }
}

void symInterfaceTypesCLASS(CLASS *c, SymbolTable *sym)
{ SYMBOL *s;
  if (c!=NULL) {
     if (c->parentname!=NULL) {
        s = getSymbol(sym,c->parentname);
        if (s==NULL) {
           reportStrError("no such parent class  %s",c->parentname,c->lineno);
           c->parent = NULL;
        } else {
           c->parent = s->val.classS;
        }
     } else {
        c->parent = NULL;
     }
     symInterfaceTypesCONSTRUCTOR(c->constructors,sym);
     symInterfaceTypesMETHOD(c->methods,sym);
  }
}

void symInterfaceTypesCONSTRUCTOR(CONSTRUCTOR *c, SymbolTable *sym)
{ if (c!=NULL) {
     symInterfaceTypesCONSTRUCTOR(c->next,sym);
     symInterfaceTypesFORMAL(c->formals,sym);
  }
}

void symInterfaceTypesMETHOD(METHOD *m, SymbolTable *sym)
{ if (m!=NULL) {
     symInterfaceTypesMETHOD(m->next,sym);
     symTYPE(m->returntype,sym);
     symInterfaceTypesFORMAL(m->formals,sym);
  }
}

void symTYPE(TYPE *t, SymbolTable *sym)
{ SYMBOL *s;
  if (t!=NULL) {
     switch (t->kind) {
       case intK:
       case boolK:
       case charK:
       case voidK:
       case polynullK:
            break;
       case refK:
            s = getSymbol(sym,t->name);
            if (s==NULL) {
               reportStrError("type identifier %s not declared",
                         t->name, t->lineno);
            } else {
               if (s->kind!=classSym) {
                  reportStrError("type %s must be a class",t->name,t->lineno);
               } else t->class = s->val.classS;
            }
     }
  }
}

void symInterfaceTypesFORMAL(FORMAL *f, SymbolTable *sym)
{ if (f!=NULL) {
     symInterfaceTypesFORMAL(f->next,sym);
     symTYPE(f->type,sym);
  }
}

void symImplementationPROGRAM(PROGRAM *p)
{ if (p!=NULL) {
     symImplementationPROGRAM(p->next);
     currentfile = p->name;
     symImplementationCLASSFILE(p->classfile);
  }
}

void symImplementationCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
     symImplementationCLASSFILE(c->next);
     symImplementationCLASS(c->class);
  }
}

void symImplementationCLASS(CLASS *c)
{ SymbolTable *sym;
  sym = scopeSymbolTable(classlib);
  symImplementationFIELD(c->fields,sym);
  symImplementationCONSTRUCTOR(c->constructors,c,sym);
  symImplementationMETHOD(c->methods,c,sym);
}

void symImplementationFIELD(FIELD *f, SymbolTable *sym)
{ SYMBOL *s;
  if (f!=NULL) {
     symImplementationFIELD(f->next,sym);
     symTYPE(f->type,sym);
     if (defSymbol(sym,f->name)) {
        reportStrError("field name %s already declared",f->name,f->lineno);
     } else {
        s = putSymbol(sym,f->name,fieldSym);
        s->val.fieldS = f;
     }
  }
}

void symImplementationCONSTRUCTOR(CONSTRUCTOR *c, CLASS *this, SymbolTable *sym)
{ SymbolTable *csym;
  if (c!=NULL) {
     symImplementationCONSTRUCTOR(c->next,this,sym);
     csym = scopeSymbolTable(sym);
     symImplementationFORMAL(c->formals,csym);
     symImplementationSTATEMENT(c->statements,this,csym,0);
  }
}

void symImplementationMETHOD(METHOD *m, CLASS *this, SymbolTable *sym)
{ SymbolTable *msym;
  if (m!=NULL) {
     symImplementationMETHOD(m->next,this,sym);
     msym = scopeSymbolTable(sym);
     symImplementationFORMAL(m->formals,msym);
     symImplementationSTATEMENT(m->statements,this,msym,m->modifier==staticMod);
  }
}

void symImplementationFORMAL(FORMAL *f, SymbolTable *sym)
{ SYMBOL *s;
  if (f!=NULL) {
     symImplementationFORMAL(f->next,sym);
     if (defSymbol(sym,f->name)) {
        reportStrError("formal %s already declared",f->name,f->lineno);
     } else {
        s = putSymbol(sym,f->name,formalSym);
        s->val.formalS = f;
     }
  }
}

void symImplementationLOCAL(LOCAL *l, SymbolTable *sym)
{ SYMBOL *s;
  if (l!=NULL) {
     symImplementationLOCAL(l->next,sym);
     symTYPE(l->type,sym);
     if (defSymbol(sym,l->name)) {
        reportStrError("local %s already declared",l->name,l->lineno);
     } else {
        s = putSymbol(sym,l->name,localSym);
        s->val.localS = l;
     }
  }
}

void symImplementationSTATEMENT(STATEMENT *s, CLASS *this, SymbolTable *sym, int stat)
{ SymbolTable *ssym;
  if (s!=NULL) {
     switch (s->kind) {
       case skipK:
            break;
       case localK:
            symImplementationLOCAL(s->val.localS,sym);
            break;
       case expK:
            symImplementationEXP(s->val.expS,this,sym,stat);
            break;
       case returnK:
            if (s->val.returnS!=NULL) {
               symImplementationEXP(s->val.returnS,this,sym,stat);
            }
            break;
       case sequenceK:
            symImplementationSTATEMENT(s->val.sequenceS.first,this,sym,stat);
            symImplementationSTATEMENT(s->val.sequenceS.second,this,sym,stat);
            break;
       case ifK:
            symImplementationEXP(s->val.ifS.condition,this,sym,stat);
            symImplementationSTATEMENT(s->val.ifS.body,this,sym,stat);
            break;
       case ifelseK:
            symImplementationEXP(s->val.ifelseS.condition,this,sym,stat);
            symImplementationSTATEMENT(s->val.ifelseS.thenpart,this,sym,stat);
            symImplementationSTATEMENT(s->val.ifelseS.elsepart,this,sym,stat);
            break;
       case whileK:
	    /* LJH - fixed Oct 13/99 
            symImplementationEXP(s->val.ifS.condition,this,sym,stat);
            symImplementationSTATEMENT(s->val.ifS.body,this,sym,stat);
	    */
            symImplementationEXP(s->val.whileS.condition,this,sym,stat);
            symImplementationSTATEMENT(s->val.whileS.body,this,sym,stat);
            break;
       case blockK:
            ssym = scopeSymbolTable(sym);
            symImplementationSTATEMENT(s->val.blockS.body,this,ssym,stat);
            break;
       case superconsK:
            symImplementationARGUMENT(s->val.superconsS.args,this,sym,stat);
            if (this->parent==NULL) s->val.superconsS.constructor = NULL;
            else s->val.superconsS.constructor = this->parent->constructors;
            break;
     }
  }
}

SYMBOL *symVar(char *name, SymbolTable *sym, CLASS *this, int lineno, int stat)
{ SYMBOL *s;
  s = getSymbol(sym,name);
  if (s==NULL) {
     s = lookupHierarchy(name,this);
     if (s==NULL) {
        reportStrError("identifier %s not declared",name,lineno);
     } else {
        if (s->kind!=fieldSym) {
           reportStrError("%s is not a variable as expected",name,lineno);
        }
     }
  } else {
     if ((s->kind!=fieldSym) && (s->kind!=formalSym) && (s->kind!=localSym)) {
        reportStrError("%s is not a variable as expected",name,lineno);
     }
  }
  if (s!=NULL && s->kind==fieldSym && stat) {
     reportStrError("illegal static reference to %s",name,lineno);
  }
  return s;
}

CLASS *symClass(char *name, SymbolTable *sym, int lineno)
{ SYMBOL *s;
  s = getSymbol(sym,name);
  if (s==NULL) {
     reportStrError("identifier %s not declared",name,lineno);
     return(NULL); /* LJH added to avoid core dump */
  } else {
     if (s->kind!=classSym) {
        reportStrError("class with name %s expected",name,lineno);
        return(NULL); /* LJH added because s might not be a class */
     }
  }
  return s->val.classS;
}

void symImplementationEXP(EXP *e, CLASS *this, SymbolTable *sym, int stat)
{ switch (e->kind) {
    case idK:
         e->val.idE.idsym = symVar(e->val.idE.name,sym,this,e->lineno,stat);
         break;
    case assignK:
         e->val.assignE.leftsym = symVar(e->val.assignE.left,sym,this,e->lineno,stat);
         symImplementationEXP(e->val.assignE.right,this,sym,stat);
         break;
    case orK:
         symImplementationEXP(e->val.orE.left,this,sym,stat);
         symImplementationEXP(e->val.orE.right,this,sym,stat);
         break;
    case andK:
         symImplementationEXP(e->val.andE.left,this,sym,stat);
         symImplementationEXP(e->val.andE.right,this,sym,stat);
         break;
    case eqK:
         symImplementationEXP(e->val.eqE.left,this,sym,stat);
         symImplementationEXP(e->val.eqE.right,this,sym,stat);
         break;
    case ltK:
         symImplementationEXP(e->val.ltE.left,this,sym,stat);
         symImplementationEXP(e->val.ltE.right,this,sym,stat);
         break;
    case gtK:
         symImplementationEXP(e->val.gtE.left,this,sym,stat);
         symImplementationEXP(e->val.gtE.right,this,sym,stat);
         break;
    case leqK:
         symImplementationEXP(e->val.leqE.left,this,sym,stat);
         symImplementationEXP(e->val.leqE.right,this,sym,stat);
         break;
    case geqK:
         symImplementationEXP(e->val.geqE.left,this,sym,stat);
         symImplementationEXP(e->val.geqE.right,this,sym,stat);
         break;
    case neqK:
         symImplementationEXP(e->val.neqE.left,this,sym,stat);
         symImplementationEXP(e->val.neqE.right,this,sym,stat);
         break;
    case instanceofK:
         symImplementationEXP(e->val.instanceofE.left,this,sym,stat);
         e->val.instanceofE.class = symClass(e->val.instanceofE.right,sym,e->lineno);
         break;
    case plusK:
         symImplementationEXP(e->val.plusE.left,this,sym,stat);
         symImplementationEXP(e->val.plusE.right,this,sym,stat);
         break;
    case minusK:
         symImplementationEXP(e->val.minusE.left,this,sym,stat);
         symImplementationEXP(e->val.minusE.right,this,sym,stat);
         break;
    case timesK:
         symImplementationEXP(e->val.timesE.left,this,sym,stat);
         symImplementationEXP(e->val.timesE.right,this,sym,stat);
         break;
    case divK:
         symImplementationEXP(e->val.divE.left,this,sym,stat);
         symImplementationEXP(e->val.divE.right,this,sym,stat);
         break;
    case modK:
         symImplementationEXP(e->val.modE.left,this,sym,stat);
         symImplementationEXP(e->val.modE.right,this,sym,stat);
         break;
    case notK:
         symImplementationEXP(e->val.notE.not,this,sym,stat);
         break;
    case uminusK:
         symImplementationEXP(e->val.uminusE,this,sym,stat);
         break;
    case thisK:
         break;
    case newK:
         e->val.newE.class = symClass(e->val.newE.name,sym,e->lineno);
         symImplementationARGUMENT(e->val.newE.args,this,sym,stat);
         break;
    case invokeK:
         symImplementationRECEIVER(e->val.invokeE.receiver,this,sym,stat);
         symImplementationARGUMENT(e->val.invokeE.args,this,sym,stat);
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
         e->val.castE.class = symClass(e->val.castE.left,sym,e->lineno);
         symImplementationEXP(e->val.castE.right,this,sym,stat);
         break;
    case charcastK:
         symImplementationEXP(e->val.charcastE,this,sym,stat);
         break;
  }
}

void symImplementationRECEIVER(RECEIVER *r, CLASS *this, SymbolTable *sym, int stat)
{ switch (r->kind) {
    case objectK:
         symImplementationEXP(r->objectR,this,sym,stat);
         break;
    case superK:
         break;
  }
}

void symImplementationARGUMENT(ARGUMENT *a, CLASS *this, SymbolTable *sym, int stat)
{ if (a!=NULL) {
     symImplementationARGUMENT(a->next,this,sym,stat);
     symImplementationEXP(a->exp,this,sym,stat);
  }
}





