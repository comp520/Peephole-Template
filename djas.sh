#!/bin/bash
# djas -  java dejasmin
PEEPDIR=`dirname $0`
java -classpath $PEEPDIR/tinapoc.jar:$PEEPDIR/bcel-5.1.jar dejasmin $*
