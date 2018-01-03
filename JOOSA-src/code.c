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
#include "code.h"
#include "symbol.h"

CODE *currentcode;
CODE *currenttail;
LABEL *currentlabels;

void appendCODE(CODE *c)
{ if (currentcode==NULL) {
     currentcode = c;
     currenttail = c;
  } else {
     currenttail->next = c;
     currenttail = c;
  }
}

void code_nop()
{ appendCODE(makeCODEnop(NULL));
}

void code_i2c()
{ appendCODE(makeCODEi2c(NULL));
}

void code_new(char *arg)
{ appendCODE(makeCODEnew(arg,NULL));
}

void code_instanceof(char *arg)
{ appendCODE(makeCODEinstanceof(arg,NULL));
}

void code_checkcast(char *arg)
{ appendCODE(makeCODEcheckcast(arg,NULL));
}

void code_imul()
{ appendCODE(makeCODEimul(NULL));
}
 
void code_ineg()
{ appendCODE(makeCODEineg(NULL));
}
 
void code_irem()
{ appendCODE(makeCODEirem(NULL));
}

void code_isub()
{ appendCODE(makeCODEisub(NULL));
}
 
void code_idiv()
{ appendCODE(makeCODEidiv(NULL));
}

void code_iadd()
{ appendCODE(makeCODEiadd(NULL));
}

CODE *code_label(char *name, int label)
{ currentlabels[label].name = name;
  currentlabels[label].sources = 1;
  appendCODE(makeCODElabel(label,NULL));
  currentlabels[label].position = currenttail;
  return currenttail;
}

void code_goto(int label)
{ appendCODE(makeCODEgoto(label,NULL));
}

void code_ifeq(int label)
{ appendCODE(makeCODEifeq(label,NULL));
}

void code_ifne(int label)
{ appendCODE(makeCODEifne(label,NULL));
}

void code_if_acmpeq(int label)
{ appendCODE(makeCODEif_acmpeq(label,NULL));
}

void code_if_acmpne(int label)
{ appendCODE(makeCODEif_acmpne(label,NULL));
}

void code_ifnull(int label)
{ appendCODE(makeCODEifnull(label,NULL));
}

void code_ifnonnull(int label)
{ appendCODE(makeCODEifnonnull(label,NULL));
}

void code_if_icmpeq(int label)
{ appendCODE(makeCODEif_icmpeq(label,NULL));
}

void code_if_icmpgt(int label)
{ appendCODE(makeCODEif_icmpgt(label,NULL));
}

void code_if_icmplt(int label)
{ appendCODE(makeCODEif_icmplt(label,NULL));
}

void code_if_icmple(int label)
{ appendCODE(makeCODEif_icmple(label,NULL));
}

void code_if_icmpge(int label)
{ appendCODE(makeCODEif_icmpge(label,NULL));
}

void code_if_icmpne(int label)
{ appendCODE(makeCODEif_icmpne(label,NULL));
}

void code_ireturn()
{ appendCODE(makeCODEireturn(NULL));
}

void code_areturn()
{ appendCODE(makeCODEareturn(NULL));
}

void code_return()
{ appendCODE(makeCODEreturn(NULL));
}
 
void code_aload(int arg)
{ appendCODE(makeCODEaload(arg,NULL));
}

void code_astore(int arg)
{ appendCODE(makeCODEastore(arg,NULL));
}

void code_iload(int arg)
{ appendCODE(makeCODEiload(arg,NULL));
}

void code_istore(int arg)
{ appendCODE(makeCODEistore(arg,NULL));
}

void code_dup()
{ appendCODE(makeCODEdup(NULL));
}

void code_pop()
{ appendCODE(makeCODEpop(NULL));
}

void code_swap()
{ appendCODE(makeCODEswap(NULL));
}

void code_ldc_int(int arg)
{ appendCODE(makeCODEldc_int(arg,NULL));
}

void code_ldc_string(char *arg)
{ appendCODE(makeCODEldc_string(arg,NULL));
}

void code_aconst_null()
{ appendCODE(makeCODEaconst_null(NULL));
}

void code_getfield(char *arg)
{ appendCODE(makeCODEgetfield(arg,NULL));
}

void code_putfield(char *arg)
{ appendCODE(makeCODEputfield(arg,NULL));
}

void code_invokevirtual(char *arg)
{ appendCODE(makeCODEinvokevirtual(arg,NULL));
}

void code_invokenonvirtual(char *arg)
{ appendCODE(makeCODEinvokenonvirtual(arg,NULL));
}

char *strcat2(char *s1, char *s2)
{ char *s;
  s = (char *)Malloc(strlen(s1)+strlen(s2)+1);
  sprintf(s,"%s%s",s1,s2);
  return s;
}

char *strcat3(char *s1, char *s2, char *s3)
{ char *s;
  s = (char *)Malloc(strlen(s1)+strlen(s2)+strlen(s3)+1);
  sprintf(s,"%s%s%s",s1,s2,s3);
  return s;
}

char *strcat4(char *s1, char *s2, char *s3, char *s4)
{ char *s;
  s = (char *)Malloc(strlen(s1)+strlen(s2)+strlen(s3)+strlen(s4)+1);
  sprintf(s,"%s%s%s%s",s1,s2,s3,s4);
  return s;
}

char *strcat5(char *s1, char *s2, char *s3, char *s4, char *s5)
{ char *s;
  s = (char *)Malloc(strlen(s1)+strlen(s2)+strlen(s3)+strlen(s4)+strlen(s5)+1);
  sprintf(s,"%s%s%s%s%s",s1,s2,s3,s4,s5);
  return s;
}

char *codePackage(char *package)
{ char *p;
  int i;
  p = (char *)Malloc(strlen(package)+2);
  for (i=0; i<strlen(package); i++) {
      if (package[i]=='.') p[i] = '/'; else p[i] = package[i];
  }
  p[i] = '/';
  p[i+1] = '\0';
  return p;
}

char *codeClassname(CLASS *c)
{ if (c->package==NULL) {
     return c->name;
  } else {
     return strcat2(codePackage(c->package),c->name);
  }
}

char *codeType(TYPE *t)
{ switch (t->kind) {
    case intK:
         return "I";
         break;
    case boolK:
         return "Z";
         break;
    case charK:
         return "C";
         break;
    case voidK:
         return "V";
         break;
    case refK:
         return strcat3("L",codeClassname(t->class),";");
         break;
    case polynullK:
         break;
  }
  return NULL;
}

char *codeFormals(FORMAL *f)
{ if (f==NULL) return "";
  return strcat2(codeFormals(f->next),codeType(f->type));
}

char *codeSignature(FORMAL *f, TYPE *t)
{ return strcat4("(",codeFormals(f),")",codeType(t));
}

char *codeConstructorSignature(FORMAL *f)
{ return strcat3("(",codeFormals(f),")V");
}

char *codeConstructor(CLASS *c, FORMAL *f)
{ return strcat3(codeClassname(c),"/<init>",codeConstructorSignature(f));
}

char *codeMethod(CLASS *c, METHOD *m)
{ return strcat4(codeClassname(c),
                 "/",
                 m->name,
                 codeSignature(m->formals,m->returntype));
}

void codePROGRAM(PROGRAM *p)
{ if (p!=NULL) {
     codePROGRAM(p->next);
     codeCLASSFILE(p->classfile);
  }
}

void codeCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
     codeCLASSFILE(c->next);
     codeCLASS(c->class);
  }
}

CLASS *currentclass;

void codeCLASS(CLASS *c)
{ currentclass = c;
  codeCONSTRUCTOR(c->constructors);
  codeMETHOD(c->methods);
  c->signature = codeClassname(c);
}

void codeCONSTRUCTOR(CONSTRUCTOR *c)
{ if (c!=NULL) {
     codeCONSTRUCTOR(c->next);
     currentcode = NULL;
     c->labels = Malloc(c->labelcount*sizeof(LABEL));
     currentlabels = c->labels;
     codeSTATEMENT(c->statements);
     code_return();
     c->opcodes = currentcode;
     c->signature = codeConstructorSignature(c->formals);
  }
}

void codeMETHOD(METHOD *m)
{ if (m!=NULL) {
     codeMETHOD(m->next);
     currentcode = NULL;
     m->labels = Malloc(m->labelcount*sizeof(LABEL));
     currentlabels = m->labels;
     codeSTATEMENT(m->statements);
     if (m->returntype->kind==voidK) {
        code_return();
     } else {
        code_nop();
     }
     m->opcodes = currentcode;
     m->signature = codeSignature(m->formals,m->returntype);
  }
}

void codeSTATEMENT(STATEMENT *s)
{ if (s!=NULL) {
     switch (s->kind) {
       case skipK:
            break;
       case localK:
            break;
       case expK:
            codeEXP(s->val.expS);
            if (s->val.expS->type->kind!=voidK) {
               code_pop();
            }
            break;
       case returnK:
            if (s->val.returnS==NULL) {
               code_return();
            } else {
               codeEXP(s->val.returnS);
               if (s->val.returnS->type->kind==refK ||
                   s->val.returnS->type->kind==polynullK) {
                  code_areturn();
               } else {
                  code_ireturn();
               }
            }
            break;
       case sequenceK:
            codeSTATEMENT(s->val.sequenceS.first);
            codeSTATEMENT(s->val.sequenceS.second);
            break;
       case ifK:
            codeEXP(s->val.ifS.condition);
            code_ifeq(s->val.ifS.stoplabel);
            codeSTATEMENT(s->val.ifS.body);
            code_label("stop",s->val.ifS.stoplabel);
            break;
       case ifelseK:
            codeEXP(s->val.ifelseS.condition);
            code_ifeq(s->val.ifelseS.elselabel);
            codeSTATEMENT(s->val.ifelseS.thenpart);
            code_goto(s->val.ifelseS.stoplabel);
            code_label("else",s->val.ifelseS.elselabel);
            codeSTATEMENT(s->val.ifelseS.elsepart);
            code_label("stop",s->val.ifelseS.stoplabel);
            break;
       case whileK:
            code_label("start",s->val.whileS.startlabel);
            codeEXP(s->val.whileS.condition);
            code_ifeq(s->val.whileS.stoplabel);
            codeSTATEMENT(s->val.whileS.body);
            code_goto(s->val.whileS.startlabel);
            code_label("stop",s->val.whileS.stoplabel);
            break;
       case blockK:
            codeSTATEMENT(s->val.blockS.body);
            break;
       case superconsK:
            code_aload(0);
            codeARGUMENT(s->val.superconsS.args); 
            code_invokenonvirtual(codeConstructor(currentclass->parent,
                                                  s->val.superconsS.constructor->formals));
            break;
     }
  }
}

void codeEXP(EXP *e)
{ if (e->tostring) {
     switch (e->type->kind) {
       case intK:
            code_new("java/lang/Integer");
            code_dup();
            break;
       case boolK:
            code_new("java/lang/Boolean");
            code_dup();
            break;
       case charK:
            code_new("java/lang/Character");
            code_dup();
            break;
       case refK:
       case voidK:
       case polynullK:
            break;
     }
  }
  switch(e->kind) {
    case idK:
         switch (e->val.idE.idsym->kind) {
           case localSym:
                if (e->val.idE.idsym->val.localS->type->kind==refK) {
                   code_aload(e->val.idE.idsym->val.localS->offset);
                } else {
                   code_iload(e->val.idE.idsym->val.localS->offset);
                }      
                break;
           case formalSym:
                if (e->val.idE.idsym->val.formalS->type->kind==refK) {
                   code_aload(e->val.idE.idsym->val.formalS->offset);
                } else {
                   code_iload(e->val.idE.idsym->val.formalS->offset);
                }
                break;
           case fieldSym:
                code_aload(0);
                code_getfield(strcat5(codeClassname(
                                      lookupHierarchyClass(e->val.idE.name,currentclass)),
                                      "/",
                                      e->val.idE.name,
                                      " ",
                                      codeType(e->val.idE.idsym->val.fieldS->type)));
                break;
           case classSym:
           case methodSym:
                break;
         }
         break;
    case assignK:
         codeEXP(e->val.assignE.right);
         code_dup();
         switch (e->val.assignE.leftsym->kind) {
           case localSym:
                if (e->val.assignE.leftsym->val.localS->type->kind==refK) {
                   code_astore(e->val.assignE.leftsym->val.localS->offset);
                } else {
                   code_istore(e->val.assignE.leftsym->val.localS->offset);
                }
                break;
           case formalSym:
                if (e->val.assignE.leftsym->val.formalS->type->kind==refK) {
                   code_astore(e->val.assignE.leftsym->val.formalS->offset);
                } else {
                   code_istore(e->val.assignE.leftsym->val.formalS->offset);
                }
                break;
           case fieldSym:
                code_aload(0);
                code_swap();
                code_putfield(strcat5(codeClassname(
                                      lookupHierarchyClass(e->val.assignE.left,currentclass)),
                                      "/",
                                      e->val.assignE.left,
                                      " ",
                                      codeType(e->val.assignE.leftsym->val.fieldS->type)));
                break;
           case classSym:
           case methodSym:
                break;
         }
         break;
    case orK:
         codeEXP(e->val.orE.left);
         code_dup();
         code_ifne(e->val.orE.truelabel);
         code_pop();
         codeEXP(e->val.orE.right);
         code_label("true",e->val.orE.truelabel);
         break;
    case andK:
         codeEXP(e->val.andE.left);
         code_dup();
         code_ifeq(e->val.andE.falselabel);
         code_pop();
         codeEXP(e->val.andE.right);
         code_label("false",e->val.andE.falselabel);
         break;
    case eqK:
         codeEXP(e->val.eqE.left);
         codeEXP(e->val.eqE.right);
         if (e->val.eqE.left->type->kind==refK ||
             e->val.eqE.left->type->kind==polynullK) {
           code_if_acmpeq(e->val.eqE.truelabel);
         } else {
           code_if_icmpeq(e->val.eqE.truelabel);
         }
         code_ldc_int(0);
         code_goto(e->val.eqE.stoplabel);
         code_label("true",e->val.eqE.truelabel);
         code_ldc_int(1);
         code_label("stop",e->val.eqE.stoplabel);
         break;
    case ltK:
         codeEXP(e->val.ltE.left);
         codeEXP(e->val.ltE.right);
         code_if_icmplt(e->val.ltE.truelabel);
         code_ldc_int(0);
         code_goto(e->val.ltE.stoplabel);
         code_label("true",e->val.ltE.truelabel);
         code_ldc_int(1);
         code_label("stop",e->val.ltE.stoplabel);
         break;
    case gtK:
         codeEXP(e->val.gtE.left);
         codeEXP(e->val.gtE.right);
         code_if_icmpgt(e->val.gtE.truelabel);
         code_ldc_int(0);
         code_goto(e->val.gtE.stoplabel);
         code_label("true",e->val.gtE.truelabel);
         code_ldc_int(1);
         code_label("stop",e->val.gtE.stoplabel);
         break;
    case leqK:
         codeEXP(e->val.leqE.left);
         codeEXP(e->val.leqE.right);
         code_if_icmple(e->val.leqE.truelabel);
         code_ldc_int(0);
         code_goto(e->val.leqE.stoplabel);
         code_label("true",e->val.leqE.truelabel);
         code_ldc_int(1);
         code_label("stop",e->val.leqE.stoplabel);
         break;
    case geqK:
         codeEXP(e->val.geqE.left);
         codeEXP(e->val.geqE.right);
         code_if_icmpge(e->val.geqE.truelabel);
         code_ldc_int(0);
         code_goto(e->val.geqE.stoplabel);
         code_label("true",e->val.geqE.truelabel);
         code_ldc_int(1);
         code_label("stop",e->val.geqE.stoplabel);
         break;
    case neqK:
         codeEXP(e->val.neqE.left);
         codeEXP(e->val.neqE.right);
         if (e->val.neqE.left->type->kind==refK ||
             e->val.eqE.left->type->kind==polynullK) {
           code_if_acmpne(e->val.neqE.truelabel);
         } else {
           code_if_icmpne(e->val.neqE.truelabel);
         }
         code_ldc_int(0);
         code_goto(e->val.neqE.stoplabel);
         code_label("true",e->val.neqE.truelabel);
         code_ldc_int(1);
         code_label("stop",e->val.neqE.stoplabel);
         break;
    case instanceofK:
         codeEXP(e->val.instanceofE.left);
         code_instanceof(codeClassname(e->val.instanceofE.class));
         break;
    case plusK:
         codeEXP(e->val.plusE.left);
         codeEXP(e->val.plusE.right);
         if (e->type->kind==intK) {
            code_iadd();
         } else {
            code_invokevirtual("java/lang/String/concat(Ljava/lang/String;)Ljava/lang/String;");
         }
         break;
    case minusK:
         codeEXP(e->val.minusE.left);
         codeEXP(e->val.minusE.right);
         code_isub();
         break;
    case timesK:
         codeEXP(e->val.timesE.left);
         codeEXP(e->val.timesE.right);
         code_imul();
         break;
    case divK:
         codeEXP(e->val.divE.left);
         codeEXP(e->val.divE.right);
         code_idiv();
         break;
    case modK:
         codeEXP(e->val.modE.left);
         codeEXP(e->val.modE.right);
         code_irem();
         break;
    case notK:
         codeEXP(e->val.notE.not);
         code_ifeq(e->val.notE.truelabel);
         code_ldc_int(0);
         code_goto(e->val.notE.stoplabel);
         code_label("true",e->val.notE.truelabel);
         code_ldc_int(1);
         code_label("stop",e->val.notE.stoplabel);
         break;
    case uminusK:
         codeEXP(e->val.uminusE);
         code_ineg();
         break;
    case thisK:
         code_aload(0);
         break;
    case newK:
         code_new(codeClassname(e->val.newE.class));
         code_dup();
         codeARGUMENT(e->val.newE.args);
         code_invokenonvirtual(codeConstructor(e->val.newE.class,
                                               e->val.newE.constructor->formals));
         break;
    case invokeK:
         codeRECEIVER(e->val.invokeE.receiver);
         codeARGUMENT(e->val.invokeE.args);
         switch (e->val.invokeE.receiver->kind) {
           case objectK:
                 { CLASS *c;
                    c = lookupHierarchyClass(e->val.invokeE.method->name,
                                             e->val.invokeE.receiver->objectR->type->class);
                    code_invokevirtual(codeMethod(c,e->val.invokeE.method));
                  }
                break;
           case superK:
                { CLASS *c;
                  c = lookupHierarchyClass(e->val.invokeE.method->name,
                                           currentclass->parent);
                  code_invokenonvirtual(codeMethod(c,e->val.invokeE.method));
                }
                break;
         }
         break;
    case intconstK:
         code_ldc_int(e->val.intconstE);
         break;
    case boolconstK:
         code_ldc_int(e->val.boolconstE);
         break;
    case charconstK:
         code_ldc_int(e->val.charconstE);
         break;
    case stringconstK:
         code_ldc_string(e->val.stringconstE);
         break;
    case nullK:
         if (e->tostring) {
            code_ldc_string("null");
         } else {
            code_aconst_null();
         }
         break;
    case castK:
         codeEXP(e->val.castE.right);
         code_checkcast(codeClassname(e->val.castE.class));
         break;
    case charcastK:
         codeEXP(e->val.charcastE);
         if (e->val.charcastE->type->kind!=charK) code_i2c();
         break;
  }
  if (e->tostring) {
     switch (e->type->kind) {
       case intK:
            code_invokenonvirtual("java/lang/Integer/<init>(I)V");
            code_invokevirtual("java/lang/Integer/toString()Ljava/lang/String;");
            break;
       case boolK:
            code_invokenonvirtual("java/lang/Boolean/<init>(Z)V");
            code_invokevirtual("java/lang/Boolean/toString()Ljava/lang/String;");
            break;
       case charK:
            code_invokenonvirtual("java/lang/Character/<init>(C)V");
            code_invokevirtual("java/lang/Character/toString()Ljava/lang/String;");
            break;
       case refK:
            code_dup();
            code_ifnull(e->nulllabel);
            if (strcmp(e->type->name,"String")!=0) {
               CLASS *c;
               c = lookupHierarchyClass("toString",e->type->class);
               code_invokevirtual(strcat2(codeClassname(c),
                                          "/toString()Ljava/lang/String;"));
            }
            code_goto(e->stoplabel);
            code_label("null",e->nulllabel);
            code_pop();
            code_ldc_string("null");
            code_label("stop",e->stoplabel);
            break;
       case voidK:
       case polynullK:
            break;
     }
  }
}

void codeRECEIVER(RECEIVER *r)
{ switch(r->kind) {
    case objectK:
         codeEXP(r->objectR);
         break;
    case superK:
         code_aload(0);
         break;
  }
}

void codeARGUMENT(ARGUMENT *a)
{ if (a!=NULL) {
     codeARGUMENT(a->next);
     codeEXP(a->exp);
  }
}
