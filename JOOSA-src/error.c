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
#include <stdlib.h>
#include "error.h"

extern char *yytext;

extern char *currentfile;

int lineno;

int errors = 0;

void yyerror(char *s)
{ fprintf(stderr,"%s\n",s);
  fprintf(stderr,"*** syntax error before %s at line %i of file %s\n",
                 yytext,lineno,currentfile);
  fprintf(stderr,"*** compilation terminated\n");
  exit(1);
}

void reportError(char *s, int lineno)
{ printf("*** %s at line %i of file %s\n",s,lineno,currentfile);
  errors++;
}

void reportStrError(char *s, char *name, int lineno)
{ printf("*** ");
  printf(s,name);
  printf(" at line %i of file %s\n",lineno,currentfile);
  errors++;
}

void reportGlobalError(char *s)
{ printf("*** %s\n",s);
  errors++;
}

void reportStrGlobalError(char *s, char *name)
{ printf("*** ");
  printf(s,name);
  printf("\n");
  errors++;
}

void noErrors()
{ if (errors!=0) {
     fprintf(stderr,"*** compilation terminated\n");
     exit(1);
  }
}
