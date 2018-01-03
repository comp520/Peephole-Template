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

void weedPROGRAM(PROGRAM *p);
void weedCLASSFILE(CLASSFILE *c);
void weedCLASS(CLASS *c);
void weedCONSTRUCTOR(CONSTRUCTOR *c);
void weedMETHOD(METHOD *m, ModifierKind classmod, int external);
int weedSTATEMENTlocals(STATEMENT *s,int localsallowed);
void weedSTATEMENTmain(STATEMENT *s);
void weedEXPmain(EXP *e);
void weedRECEIVERmain(RECEIVER *r);
void weedARGUMENTmain(ARGUMENT *a);
int weedSTATEMENTreturns(STATEMENT *s);

