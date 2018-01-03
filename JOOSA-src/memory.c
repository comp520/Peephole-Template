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

void *Malloc(unsigned n)
{ void *p;

  if (!(p = malloc(n))) {
     fprintf(stderr,"Malloc(%d) failed.\n",n);
     fflush(stderr);
     abort();
   }
   return p;
}
