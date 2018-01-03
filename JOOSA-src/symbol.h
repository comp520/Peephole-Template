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

#define HashSize 317

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *next;
} SymbolTable;

SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind);

SYMBOL *getSymbol(SymbolTable *t, char *name);

int defSymbol(SymbolTable *t, char *name);

int subClass(CLASS *sub, CLASS *super);

SYMBOL *lookupHierarchy(char *name, CLASS *start);

CLASS *lookupHierarchyClass(char *name, CLASS *start);

SymbolTable *classlib;

void symPROGRAM(PROGRAM *p);
void symInterfacePROGRAM(PROGRAM *p, SymbolTable *sym);
void symInterfaceCLASSFILE(CLASSFILE *c, SymbolTable *sym);
void symInterfaceCLASS(CLASS *c, SymbolTable *sym);
void symInterfaceCONSTRUCTOR(CONSTRUCTOR *c, char *classname, SymbolTable *sym);
void symInterfaceMETHOD(METHOD *m, SymbolTable *sym);
void symInterfaceTypesPROGRAM(PROGRAM *p, SymbolTable *sym);
void symInterfaceTypesCLASSFILE(CLASSFILE *c, SymbolTable *sym);
void symInterfaceTypesCLASS(CLASS *c, SymbolTable *sym);
void symInterfaceFIELD(FIELD *f, SymbolTable *sym);
void symInterfaceTypesCONSTRUCTOR(CONSTRUCTOR *c, SymbolTable *sym);
void symInterfaceTypesMETHOD(METHOD *m, SymbolTable *sym);
void symTYPE(TYPE *t, SymbolTable *sym);
void symInterfaceTypesFORMAL(FORMAL *f, SymbolTable *sym);
void symImplementationPROGRAM(PROGRAM *p);
void symImplementationCLASSFILE(CLASSFILE *c);
void symImplementationCLASS(CLASS *c);
void symImplementationFIELD(FIELD *f, SymbolTable *sym);
void symImplementationCONSTRUCTOR(CONSTRUCTOR *c, CLASS *parent, SymbolTable *sym);
void symImplementationMETHOD(METHOD *m, CLASS *parent, SymbolTable *sym);
void symImplementationFORMAL(FORMAL *f, SymbolTable *sym);
void symImplementationSTATEMENT(STATEMENT *s, CLASS *parent, SymbolTable *sym, int stat);
void symImplementationLOCAL(LOCAL *l, SymbolTable *sym);
void symImplementationEXP(EXP *e, CLASS *parent, SymbolTable *sym, int stat);
void symImplementationRECEIVER(RECEIVER *r, CLASS *parent, SymbolTable *sym, int stat);
void symImplementationARGUMENT(ARGUMENT *a, CLASS *parent, SymbolTable *sym, int stat);

