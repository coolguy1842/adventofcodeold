@echo off

del main.exe

g++ -std=c++20 -ffast-math -O3 -Wall -o main main.cpp -I days -I include -pipe
.\main.exe
