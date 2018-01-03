#!/bin/bash
#
# joosc: compiles JOOS source programs into class files using the A- JOOS compiler.
#
# usage:  joosc f1.java f2.java ... fn.joos
#  
# note:  you should name each source file for ordinary classes with
#        .java extensions and all external classes with .joos extensions

PEEPDIR=`dirname $0`
$PEEPDIR/joos.sh $*

for f in $*
do
	if [[ $f != "-O" && ${f##*.} != "joos" ]]
	then
		NAME=${f%.*}
		java -jar $PEEPDIR/jasmin.jar $NAME.j 
		if [ $1 == "-O" ]
		then
			$PEEPDIR/djas.sh -w $NAME.class > $NAME.optdump
		else
			$PEEPDIR/djas.sh -w $NAME.class > $NAME.dump
		fi
	fi
done
