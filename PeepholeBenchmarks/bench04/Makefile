all: clean
	$(PEEPDIR)/joosc.sh *.java 

opt: clean
	$(PEEPDIR)/joosc.sh -O *.java 

java:
	javac *.java

clean:	
	rm -rf *.class *.j *~ newout

run:
	java -classpath "$(PEEPDIR)/jooslib.jar:." Game < in1

diff:
	java -classpath "$(PEEPDIR)/jooslib.jar:." Game < in1 > newout; diff out1 newout
