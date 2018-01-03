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

void typePROGRAM(PROGRAM *p);
void typeHierarchyPROGRAM(PROGRAM *p);
void typeHierarchyCLASSFILE(CLASSFILE *f);
void typeHierarchyCLASS(CLASS *c);
void typeHierarchyFIELD(FIELD *f, CLASS *this);
void typeHierarchyMETHOD(METHOD *m,  CLASS *this);
void typeImplementationPROGRAM(PROGRAM *p);
void typeImplementationCLASSFILE(CLASSFILE *c);
void typeImplementationCLASS(CLASS *c);
void typeImplementationCONSTRUCTOR(CONSTRUCTOR *c, CLASS *class);
void typeImplementationMETHOD(METHOD *m, CLASS *class);
void typeImplementationSTATEMENT(STATEMENT *s, CLASS *class, TYPE *returntype);
void typeImplementationEXP(EXP *e, CLASS *class);
void typeImplementationARGUMENT(ARGUMENT *a, CLASS *class);
TYPE *typeImplementationRECEIVER(RECEIVER *r, CLASS *class);
void typeImplementationFORMALARGUMENT(FORMAL *f, ARGUMENT *a, int lineno);

