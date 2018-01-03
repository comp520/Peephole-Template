# Peephole Template

An introduction to the basics of peephole optimization using Java Bytecode and JOOS.

## Directory Structure

### JOOS
* `JOOSA-src/`: Source code for the A+ JOOS compiler (excluding the A+ patterns). It is thus more complete than the A- compiler distributed previously. For example, it supports for loops, increment expressions, and proper computation of stack height
  * `patterns.h`: Source file containing all your patterns for this assignment. We have included a few sample patterns to get you started, but you should add many more!
* `JOOSexterns/`: The `.joos` files that define the external signatures. They are included by the scripts
* `JOOSlib/`: The `.java` files that serve as interfaces to Java functionality
* `jasmin.jar`: A copy of jasmin, used by the `joosc.sh` script
* `jooslib.jar`: A copy of the JOOS library
* `joos.sh`:  Script that calls the joos compiler in `JOOSA-src/` directory. It produces one `.j` file for each input `.java` file
* `joosc.sh`: Script that calls the joos compiler to generate the `.j` files and then calls jasmin to generate the `.class` files. You should be able to run those `.class` files with any Java system

### Convenience
* `PeepholeBenchmarks/`: There are 6 benchmarks in this directory that you can use for testing your optimizations. Each benchmark contains a Makefile that you can use to compile. Optimizations are appled when invoking `make opt`. Note that you must set the $PEEPDIR environment variable to directly invoke the Makefile
* `count.sh`: Script that compiles all benchmarks with/without optimization and reports the bytecode size in both cases. This will likely be the sole command you run to compile and test
