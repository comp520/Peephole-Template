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
#include "optimize.h"

/*****  isA  functions,  return true if the instruction pointed to by
 *****  the parameter c is an instruction of the given kind.
 ****   Will return false if c is NULL.
 ****   If the return value is true, will set 
 ****   values all params other than the first as a side-effect.  ****/

int is_nop(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==nopCK;
}

int is_i2c(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==i2cCK;
}

int is_new(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == newCK) {
     (*arg) = c->val.newC;
     return 1;
  } else {
     return 0;
  }
}

int is_instanceof(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == instanceofCK) {
     (*arg) = c->val.instanceofC;
     return 1;
  } else {
     return 0;
  }
}

int is_checkcast(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == checkcastCK) {
     (*arg) = c->val.checkcastC;
     return 1;
  } else {
     return 0;
  }
}

int is_imul(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==imulCK;
}

int is_ineg(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==inegCK;
}

int is_irem(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==iremCK;
}

int is_isub(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==isubCK;
}

int is_idiv(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==idivCK;
}

int is_iadd(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==iaddCK;
}

int is_iinc(CODE *c, int *offset, int *amount)
{ if (c==NULL) return 0;
  if (c->kind == iincCK) {
     (*offset) = c->val.iincC.offset;
     (*amount) = c->val.iincC.amount;
     return 1;
  } else {
     return 0;
  }
}

int is_label(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == labelCK) {
     (*label) = c->val.labelC;
     return 1;
  } else {
     return 0;
  }
}

int is_goto(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == gotoCK) {
     (*label) = c->val.gotoC;
     return 1;
  } else {
     return 0;
  }
}


int is_ifeq(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == ifeqCK) {
     (*label) = c->val.ifeqC;
     return 1;
  } else {
     return 0;
  }
}

int is_ifne(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == ifneCK) {
     (*label) = c->val.ifneC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_acmpeq(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_acmpeqCK) {
     (*label) = c->val.if_acmpeqC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_acmpne(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_acmpneCK) {
     (*label) = c->val.if_acmpneC;
     return 1;
  } else {
     return 0;
  }
}

int is_ifnull(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == ifnullCK) {
     (*label) = c->val.ifnullC;
     return 1;
  } else {
     return 0;
  }
}

int is_ifnonnull(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == ifnonnullCK) {
     (*label) = c->val.ifnonnullC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_icmpeq(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_icmpeqCK) {
     (*label) = c->val.if_icmpeqC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_icmpgt(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_icmpgtCK) {
     (*label) = c->val.if_icmpgtC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_icmplt(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_icmpltCK) {
     (*label) = c->val.if_icmpltC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_icmple(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_icmpleCK) {
     (*label) = c->val.if_icmpleC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_icmpge(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_icmpgeCK) {
     (*label) = c->val.if_icmpgeC;
     return 1;
  } else {
     return 0;
  }
}

int is_if_icmpne(CODE *c, int *label)
{ if (c==NULL) return 0;
  if (c->kind == if_icmpneCK) {
     (*label) = c->val.if_icmpneC;
     return 1;
  } else {
     return 0;
  }
}


/*
 * is_if - return true if the node is a if statement, 
 * and modify the content of the label pointer to be the value of the label. 
 */
 
int is_if(CODE **c, int *label)
{
  if (is_ifeq(*c, label) ||
      is_ifne(*c, label) ||
      is_if_acmpeq(*c, label) ||
      is_if_acmpne(*c, label) ||
      is_ifnull(*c, label) ||
      is_ifnonnull(*c, label) ||
      is_if_icmpeq(*c, label) ||
      is_if_icmpgt(*c, label) ||
      is_if_icmplt(*c, label) ||
      is_if_icmple(*c, label) ||
      is_if_icmpge(*c, label) ||
      is_if_icmpne(*c, label))
      return 1;
  return 0;
}


int is_ireturn(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==ireturnCK;
}

int is_areturn(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==areturnCK;
}

int is_return(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==returnCK;
}

int is_aload(CODE *c, int *arg)
{ if (c==NULL) return 0;
  if (c->kind == aloadCK) {
     (*arg) = c->val.aloadC;
     return 1;
  } else {
     return 0;
  }
}

int is_astore(CODE *c, int *arg)
{ if (c==NULL) return 0;
  if (c->kind == astoreCK) {
     (*arg) = c->val.astoreC;
     return 1;
  } else {
     return 0;
  }
}

int is_iload(CODE *c, int *arg)
{ if (c==NULL) return 0;
  if (c->kind == iloadCK) {
     (*arg) = c->val.iloadC;
     return 1;
  } else {
     return 0;
  }
}

int is_istore(CODE *c, int *arg)
{ if (c==NULL) return 0;
  if (c->kind == istoreCK) {
     (*arg) = c->val.istoreC;
     return 1;
  } else {
     return 0;
  }
}

int is_dup(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==dupCK;
}

int is_pop(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==popCK;
}

int is_swap(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==swapCK;
}

int is_ldc_int(CODE *c, int *arg)
{ if (c==NULL) return 0;
  if (c->kind == ldc_intCK) {
     (*arg) = c->val.ldc_intC;
     return 1;
  } else {
     return 0;
  }
}

int is_ldc_string(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == ldc_stringCK) {
     (*arg) = c->val.ldc_stringC;
     return 1;
  } else {
     return 0;
  }
}

int is_aconst_null(CODE *c)
{ if (c==NULL) return 0;
  return c->kind==aconst_nullCK;
}

int is_getfield(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == getfieldCK) {
     (*arg) = c->val.getfieldC;
     return 1;
  } else {
     return 0;
  }
}

int is_putfield(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == putfieldCK) {
     (*arg) = c->val.putfieldC;
     return 1;
  } else {
     return 0;
  }
}

int is_invokevirtual(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == invokevirtualCK) {
     (*arg) = c->val.invokevirtualC;
     return 1;
  } else {
     return 0;
  }
}

int is_invokenonvirtual(CODE *c, char **arg)
{ if (c==NULL) return 0;
  if (c->kind == invokenonvirtualCK) {
     (*arg) = c->val.invokenonvirtualC;
     return 1;
  } else {
     return 0;
  }
}

int is_empty(CODE *c)
{ return c==NULL;
}

int is_simplepush(CODE *c)
{ if (c==NULL) return 0;
  return (c->kind==aloadCK) || (c->kind==iloadCK) || (c->kind==ldc_intCK) || 
         (c->kind==ldc_stringCK) || (c->kind==aconst_nullCK);
}


/**** Helper functions for getting the next instruction *****/

CODE * next(CODE *c)
{ if (c==NULL) return NULL;
  return c->next;
}

CODE * nextby(CODE *c, int by) {
  while (by-- > 0) {
      if (c==NULL) return NULL;
      c = c->next;
  }
  return c;
}

/******   Helper functions for dealing with labels ******/

int uses_label(CODE *c, int *label)
{ if (c==NULL) return 0;
  return is_goto(c,label) || is_ifeq(c,label) || is_ifne(c,label) || 
         is_if_acmpeq(c,label) || is_if_acmpne(c,label) || 
         is_ifnull(c,label) || is_ifnonnull(c,label) ||
         is_if_icmpeq(c,label) || is_if_icmpgt(c,label) || 
         is_if_icmplt(c,label) || is_if_icmple(c,label) || 
         is_if_icmpge(c,label) || is_if_icmpne(c,label);
}

LABEL *currentlabels;   /* points to current labels table */
LABEL **currentlabelstable; /* pointer to field in AST 
			       pointing to labels table */
int currentlabelstablesize;
int _label; /* current offset of last used label */

CODE *destination(int label)
{ return currentlabels[label].position;
}

int copylabel(int label)
{ currentlabels[label].sources++;
  return label;
}

void droplabel(int label)
{ currentlabels[label].sources--;
}

int deadlabel(int label)
{ return currentlabels[label].sources==0;
}

int uniquelabel(int label)
{ return currentlabels[label].sources==1;
}

/* returns next available index into label table.  If the table is full
 * it doubles the size of the table, copying old entries into the new table
 * and then fixing the pointer from the AST to this new table.
 */  
int next_label()
{ int i;
    
  _label++;
  if (_label==currentlabelstablesize)
    { /* allocate new table, double the size */ 
      currentlabels=Malloc(currentlabelstablesize*2*sizeof(LABEL));
      /* copy entries to new table */
      for (i=0;i<currentlabelstablesize;i++)
        currentlabels[i]=(*currentlabelstable)[i];
      currentlabelstablesize*=2;
      /* fixup pointer in AST to new table */
      *currentlabelstable=currentlabels;
    }
  return(_label);
}


/* inserts a new entry in label table */
void INSERTnewlabel(int i,char* name,CODE *target,int count)
{ currentlabels[i].name = name;
  currentlabels[i].position = target;
  currentlabels[i].sources = count;
}


/***** Helper functions to replace k instructions starting at at c by 
       the sequence of Code pointed to by r.   *****/

/* Replaces a sequence of instructions by another.  WARNING: Make sure the
 * k instructions you are removing cannot be branched into from pieces of code 
 * outside of the part you are removing.
 * If you remove instructions that branch to a label you must explicitly
 * do a droplabel for them.  (see replace_modified below that will do this
 * automatically for you)
 */ 
int replace(CODE **c, int k, CODE *r)
{ CODE *p;
  int i;
  p = *c;
  for (i=0; i<k; i++) p=p->next;
  if (r==NULL) {
     *c = p;
  } else {
     *c = r;
     while (r->next!=NULL) r=r->next;
     r->next = p;
  }
  return 1;
}

/*  
 *  Replace_modified - replaces a sequence of instructions by another one
 *  Changes have been made to automatically drop labels if needed.
 */
int replace_modified(CODE **c, int k, CODE *r)
{ CODE *p;
  int i;
  p = *c;
 for (i=0; i<k; i++) {
   int label;
   if (uses_label(p, &label) && !deadlabel(label))
     droplabel(label);
   p=p->next;
  }
  if (r==NULL) {
      *c = p;
    }
  else {
    *c = r;
    while (r->next!=NULL) r=r->next;
    r->next = p;
  }
  return 1;
}
 
/*
 * kill_line - simply removes the line *c from the bytecode, drops labels
 *             if needed.
 */
int kill_line(CODE **c)
{
  return replace_modified(c,1,NULL);
}

/*
 * stack_effect -  computes three quantities given a line of code:
 * 1. inc contains the height difference of the stack after the operation.
 * 2. affected contains the lowest element on the stack affected by this 
 *    bytecode.
 * 3. used contains the lowest element on the stack used by this bytecode 
 * (Positions are relative to the starting point).
 * e.g
 * For a swap operation inc=0, affected = -2, used=-2.
 * For a load operation, inc=+1, affected = 0, used=0.
 * For a dup operation, inc=1, affected=0, used=-1. 
 *
 * Note that we always have :
 * used<=affected.
 * affected<=0
 *
 * The return value of the function tell the user if the the code is of 
 * a type which might invalidate stack analysis:
 * 0: normal
 * 1: goto
 * 2: comparison
 * 3: label
 * 4: return
 */

int stack_effect(CODE *c, int *inc, int *affected, int *used)
{
  char *stringpos;
  if(c!=NULL) {
    
  switch(c->kind) {
    case nopCK:
	case iincCK:
      *inc=*used=*affected=0;
      break;
      
	case instanceofCK:
    case getfieldCK:	
    case i2cCK:
    case inegCK:
      *inc=0;
      *used=*affected=-1;
      break;
      
    case checkcastCK:
      *inc = *affected =0;
      *used= -1;
      break;
    
    case swapCK:
      *inc=0;
      *used=*affected=-2;
      break;

    case labelCK:
      *inc=*used=*affected=0;
      return 3;
      break; 
      
    case newCK:
    case iloadCK:
    case aloadCK:
    case ldc_intCK:
    case ldc_stringCK:
    case aconst_nullCK:
      *inc = +1;
      *affected=*used=0;
      break;
      
    case dupCK:
      *inc=1;
      *affected=0;
      *used=-1;
      break;
      
    case popCK:	
    case istoreCK:
    case astoreCK:
      *inc=*used=*affected= -1;
      break;

    case iremCK:
    case isubCK:
    case idivCK:
    case iaddCK:
    case imulCK:
      *inc=-1;
      *used=*affected=-2;
      break;
      
    case putfieldCK:
      *used=*affected=*inc = -2;
      break;
      
    case invokevirtualCK:
    case invokenonvirtualCK:
      *inc=-1; /* receiver */
      if(c->kind==invokevirtualCK)
        stringpos = c->val.invokevirtualC;
      else
        stringpos = c->val.invokenonvirtualC;
      
      while((*stringpos) != '(') stringpos++;
      stringpos++;

      /* one for each formal */
      while((*stringpos) != ')') {
        (*inc)--;
        if((*stringpos)=='L')
          while((*stringpos)!=';') stringpos++;
        stringpos++;
      }
      stringpos++;

      *used = *affected = *inc;	

      /* if not void, then pushes return value */
      if((*stringpos)!='V')
        (*inc)++;
      break;
      
    case gotoCK:
      *used = *affected = *inc =0;
      return 1;
      break;
      
    case ifeqCK:
    case ifneCK:
    case ifnullCK:
    case ifnonnullCK:
      *inc = *used = *affected = -1;
      return 2;
      break;
      
    case if_icmpeqCK:
    case if_icmpneCK:
    case if_icmpgtCK:
    case if_icmpltCK:
    case if_icmpleCK:
    case if_icmpgeCK:
    case if_acmpeqCK:
    case if_acmpneCK:
      *inc = *used = *affected = -2;
      return 2;
      break;
      
    case returnCK:
      *inc = *used = *affected = 0;
      return 4;
    case areturnCK:
    case ireturnCK:
      *inc = *used = *affected = -1;
      return 4;
      break;
      
    default:
      printf("Stack_Effect: unrecognized code kind\n");
      *inc=*used=*affected=0;
      break;
    }
  }
  return 0;  
}

typedef int(*OPTI)(CODE **);

/*************************  MAIN OPTIMIZATION LOOP **********************/

int add_pattern(char *name, OPTI pattern);

#define ADD_PATTERN(x) add_pattern(#x, x)

/* Here is a null_pattern that is usefull as a place holder in your array. */
int null_pattern(CODE **c)  { return 0; }

/* Your patterns get included here */
#include "patterns.h"

/* Fabien: modifications to improve peephole framework */
/* Fall00 and before: optimization and OPTS were defined in patterns.h */

#ifndef OPTS

#define MAX_PATTERNS 100

char *opti_name[MAX_PATTERNS]; /* name of the patterns */
OPTI optimization[MAX_PATTERNS];
int frequencies[MAX_PATTERNS];
int OPTS = 0;

int add_pattern(char *name, OPTI pattern)
{
	if (OPTS > MAX_PATTERNS) {
		printf ("cannot add any more pattern");
		return 0;
	}
	opti_name[OPTS] = name;
	optimization[OPTS] = pattern;
	OPTS++;
	return 1;
}
#else
int frequencies[OPTS];
/* dummy add_pattern, because it should not be used in that case */
int add_pattern(char *name, OPTI pattern) {return 0;}
#endif /* ifndef OPTS */


int optiCHANGE;

void optiCODEtraverse(CODE **c)
{ int i,change;
  change = 1;
  if (*c!=NULL) {
     while (change) {
       change = 0;
       for (i=0; i<OPTS; i++) {
	  int optimized;
	  optimized = optimization[i](c);
	  if (optimized) frequencies[i]++;
          change = change | optimized;
       }
       optiCHANGE = optiCHANGE || change;
     }
     if (*c!=NULL) optiCODEtraverse(&((*c)->next));
  }
} 

void optiCODE(CODE **c)
{ optiCHANGE = 1;
  while (optiCHANGE) {
    optiCHANGE = 0;
    optiCODEtraverse(c);
  }
}

void optiPROGRAMrec(PROGRAM *p)
{ if (p!=NULL) {
    optiPROGRAMrec(p->next);
    optiCLASSFILE(p->classfile);
  }
}

void optiPROGRAM(PROGRAM *p)
{
  int i;
  for(i = 0; i < OPTS; i++)
    frequencies[i] = 0;

#ifndef OPTS
  init_patterns();
#endif
  
  if (p!=NULL) {
    optiPROGRAMrec(p->next);
    optiCLASSFILE(p->classfile);
  }

  printf("\nFrequencies:\n");
  for(i = 0; i < OPTS; i++)
#ifdef OPTS
      printf("%d\t", frequencies[i]);
#else
      printf("%s: %d\n", opti_name[i], frequencies[i]);
#endif
  
  printf("\n");
}

void optiCLASSFILE(CLASSFILE *c)
{ if (c!=NULL) {
     optiCLASSFILE(c->next);
     optiCLASS(c->class);
  }
}

void optiCLASS(CLASS *c)
{ if (!c->external) {
     optiCONSTRUCTOR(c->constructors);
     optiMETHOD(c->methods);
  }
}

void optiCONSTRUCTOR(CONSTRUCTOR *c)
{ if (c!=NULL) {
     optiCONSTRUCTOR(c->next);
     currentlabels = c->labels;
     currentlabelstable = &(c->labels);
     currentlabelstablesize = c->labelcount;
     _label=currentlabelstablesize-1;
     optiCODE(&c->opcodes);
     /* Feng fix */
     c->labelcount=_label+1;
  }
}

void optiMETHOD(METHOD *m)
{ if (m!=NULL) {
     optiMETHOD(m->next);
     currentlabels = m->labels;
     currentlabelstable = &(m->labels);
     currentlabelstablesize = m->labelcount;
     _label=currentlabelstablesize-1;
     optiCODE(&m->opcodes);
     /* Feng fix */
     m->labelcount=_label+1;
  }
}
