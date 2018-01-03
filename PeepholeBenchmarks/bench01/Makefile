all: clean
	$(PEEPDIR)/joosc.sh *.java

opt: clean
	$(PEEPDIR)/joosc.sh -O *.java

java:
	javac *.java

clean:	
	rm -rf *.class *.j *~ newout

run:
	java -cp "$(PEEPDIR)/jooslib.jar:." Benchmark < in1

diff:
	java -cp "$(PEEPDIR)/jooslib.jar:." Benchmark < in1 > newout; diff out1 newout
