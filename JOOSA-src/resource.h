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

void resPROGRAM(PROGRAM *p);
void resCLASSFILE(CLASSFILE *c);
void resCLASS(CLASS *c);
void resCONSTRUCTOR(CONSTRUCTOR *c);
void resMETHOD(METHOD *m);
void resFORMAL(FORMAL *f);
void resSTATEMENT(STATEMENT *s);
void resEXP(EXP *e);
void resLOCAL(LOCAL *l);
void resRECEIVER(RECEIVER *r);
void resARGUMENT(ARGUMENT *a);
