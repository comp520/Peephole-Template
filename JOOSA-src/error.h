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

void yyerror(char *s);

void reportError(char *s, int lineno);

void reportStrError(char *s, char *name, int lineno);

void reportGlobalError(char *s);

void reportStrGlobalError(char *s, char *name);

void noErrors();

extern int lineno;
