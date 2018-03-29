all:
	$(PEEPDIR)/joosc.sh *.java

opt:
	$(PEEPDIR)/joosc.sh -O *.java

java:
	javac *.java

clean:	
	rm -rf *.class *.j *~ newout *.dump *.optdump

run:
	java -cp "$(PEEPDIR)/jooslib.jar:." Benchmark < in1

diff:
	java -cp "$(PEEPDIR)/jooslib.jar:." Benchmark < in1 > newout; diff out1 newout
