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
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tree.h"
#include "error.h"
#include "weed.h"
#include "symbol.h"
#include "type.h"
#include "defasn.h"
#include "resource.h"
#include "code.h"
#include "optimize.h"
#include "emit.h"

void yyparse();

char *currentfile;

PROGRAM *theprogram;
CLASSFILE *theclassfile;

int optionO;

int main(int argc, char **argv)
{ int i;
  theprogram = NULL;
  optionO = 0;
  for (i=1; i<argc; i++) {
      if (strcmp(argv[i],"-O")==0) {
         optionO = 1;
      } else {
         currentfile = argv[i];
         if (freopen(currentfile,"r",stdin) != NULL)
           { lineno = 1;
             yyparse();
             theprogram = makePROGRAM(currentfile,theclassfile,theprogram);
           }
         else {
           reportStrGlobalError("Unable to open file %s ",currentfile);
         }
      }
  }
  noErrors();
  weedPROGRAM(theprogram);
  noErrors();
  symPROGRAM(theprogram);
  noErrors();
  typePROGRAM(theprogram);
  noErrors();
  defasnPROGRAM(theprogram);
  noErrors();
  resPROGRAM(theprogram);
  codePROGRAM(theprogram);
  if (optionO) optiPROGRAM(theprogram);
  emitPROGRAM(theprogram);
  return 0;
}
