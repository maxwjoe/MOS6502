#!/bin/bash

# Bash script to compile emulator and tests, then run testbed 

cd emulator 
make clean
make 
echo EMULATOR BUILT
cd ../
cd test
make clean
make
echo TEST BUILT
./bin/testBed
cd ../