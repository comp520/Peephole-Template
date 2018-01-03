#!/bin/bash
# Compile JOOS programs using the A- compiler.

PEEPDIR=`dirname $0`
$PEEPDIR/JOOSA-src/joos $* $PEEPDIR/JOOSexterns/*.joos
