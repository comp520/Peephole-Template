all:
	$(PEEPDIR)/joosc.sh *.java *.joos
	make -C lib

opt:
	$(PEEPDIR)/joosc.sh -O *.java *.joos
	make -C lib

java:
	javac *.java
	make -C lib

clean:	
	rm -rf *.class *.j *~ newout *.dump *.optdump
	make -C lib clean

run:
	java -classpath "$(PEEPDIR)/jooslib.jar:.:lib/" Main < in1

diff:
	java -classpath "$(PEEPDIR)/jooslib.jar:lib/:." Main < in1 > newout; diff out1 newout
