#!/bin/sh
g++ -O2 gen.cpp
./a.out > temp.txt
g++ -O2 main.cpp
hyperfine './a.out < temp.txt > temp_out.txt'
cat temp.txt > temp_test.txt
cat temp_out.txt >> temp_test.txt
g++ -O2 verify.cpp
./a.out < temp_test.txt
