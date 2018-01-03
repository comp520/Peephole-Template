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

#include "tree.h"

typedef struct ASNSET {
  enum {singleK,intersectK,unionK,universalK} kind;
  union {
    struct LOCAL *singleS;
    struct {struct ASNSET *first,*second;} intersectS;
    struct {struct ASNSET *first,*second;} unionS;
  } val;
  struct ASNSET *next; 
} ASNSET;

void defasnPROGRAM(PROGRAM *p);
void defasnCLASSFILE(CLASSFILE *c);
void defasnCLASS(CLASS *c);
void defasnCONSTRUCTOR(CONSTRUCTOR *c);
void defasnMETHOD(METHOD *m);
ASNSET *defasnSTATEMENT(STATEMENT *s, ASNSET *before);
ASNSET *defasnEXPassume(EXP *e, ASNSET *before, int assume);
ASNSET *defasnEXP(EXP *e, ASNSET *before);
ASNSET *defasnRECEIVER(RECEIVER *r, ASNSET *before);
ASNSET *defasnARGUMENT(ARGUMENT *a, ASNSET *before);

