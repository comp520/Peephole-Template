#!/bin/bash

make -C JOOSA-src clean
rm -f PeepholeBenchmarks/bench*/*.*dump

for BENCH_DIR in PeepholeBenchmarks/*/; do
	make -C $BENCH_DIR clean
done
