#!/bin/bash

# Bash script to compile emulator and tests, then run

cd emulator 
make clean
make 
cd ../
cd test
make clean
make
./bin/testBed
cd ../