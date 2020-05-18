#!/bin/sh
g++ -O2 main.cpp
hyperfine --warmup 50 -m 50 './a.out < data/ex4.txt > data/ex4out.txt'