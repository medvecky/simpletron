#!/bin/bash

cd cpputest
make clean
cd cpputest_build
autoreconf .. -i
cd ..
./configure
make
export CPPUTEST_HOME=cpputest 
