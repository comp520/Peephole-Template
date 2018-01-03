CC = gcc

# Select the first one when using bison,  and the second one when using byacc
YACCOPTS = bison -y -d
#YACCOPTS = byacc -d  -v 

# Select the first one when compiling on a real unix sytem,  second one 
# when using gcc under Windows
CFLAGS = -Wall -ansi -pedantic -g
#CFLAGS = 

main: y.tab.o lex.yy.o main.o tree.h tree.o error.h error.o memory.h memory.o weed.h weed.o symbol.h symbol.o type.h type.o defasn.h defasn.o resource.h resource.o code.h code.o optimize.h optimize.o emit.h emit.o
	$(CC) lex.yy.o y.tab.o tree.o error.o memory.o weed.o symbol.o type.o defasn.o resource.o code.o optimize.o emit.o main.o -o joos -lfl

optimize.o: optimize.c patterns.h
	$(CC) $(CFLAGS) -c optimize.c
	
y.tab.c y.tab.h: joos.y
	$(YACCOPTS) joos.y

lex.yy.c: joos.l y.tab.h 
	flex joos.l

clean:
	rm *.o lex.* y.tab.* joos

