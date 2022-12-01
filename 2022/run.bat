@echo off

del main.exe

g++ -O3 -Wall -o main main.cpp -I days -I include
.\main.exe
