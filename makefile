##Makefile for the project

COMPILER = g++
CCFLAGS1 = -g
CCFLAGS2 = -Wall

PROJECT:
	g++ -std=c++11 main.cpp Trie.cpp Board.cpp