CC = g++
CPPFLAGS := -g 
OUT_DIR = ../obj/

OBJS = utils.o leetcode_solutions.o
SRCS = utils.cpp leetcode_solutions.cpp

leetcode_solutions.o : leetcode_solutions.cpp utils.h
	$(CC) $(CPPFLAGS) -c $< -o $(OUT_DIR)$@
utils.o : utils.cpp utils.h
	$(CC) $(CPPFLAGS) -c $< -o $(OUT_DIR)$@

.PHONY : all
all : $(OBJS)
