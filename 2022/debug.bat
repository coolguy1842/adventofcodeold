@echo off

del main.exe

g++ -std=c++20 -ffast-math -O0 -g3 -ggdb -Wall -o main main.cpp -I days -I include -pipe
gdb .\main.exe
