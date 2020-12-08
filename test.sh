#!/bin/bash
# $1: on/off

TIMEFORMAT=%2U
name="tab"
timer () {
  for i in {0..1000}
  do
    ./$name.exe < $name.inp > /dev/null
  done
}

g++ $name.cpp -o $name.exe

echo "" > time-$1.out; 
for i in {1..50}; do (time timer) 2>> time-$1.out; done