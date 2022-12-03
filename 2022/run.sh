#!/bin/bash

rm main

g++ -O3 -Wall -o main main.cpp -I days -I include
./main