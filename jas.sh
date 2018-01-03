#! /bin/bash
# jas - java jasmin
PEEPDIR=`dirname $0`
java -classpath $PEEPDIR/tinapoc.jar:$PEEPDIR/bcel-5.1.jar jasmin $*
