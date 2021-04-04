#!/bin/sh
gcc -Wall "src/$1" && ./a.out < "data/$2"