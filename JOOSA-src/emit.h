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
 
void emitPROGRAM(PROGRAM *p);
void emitCLASSFILE(CLASSFILE *c, char *name);
void emitCLASS(CLASS *c, char *name);
void emitTYPE(TYPE *t);
void emitFIELD(FIELD *f);
void emitCONSTRUCTOR(CONSTRUCTOR *c);
void emitMETHOD(METHOD *m);
void emitMODIFIER(ModifierKind modifier);

