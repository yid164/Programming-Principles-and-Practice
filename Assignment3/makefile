# makefile for Assignment3
# Author: Yinsheng Dong
# Student Number: 11148648
# NSID: yid164
# Lecture section: CMPT 214 

# make(1) uses $(CC) for linking object files.
# Cannot link C++ files with the C compiler, so
# we have to set the CC variable to the C++ compiler
CC = $(CXX)
CXX = g++
CXXFLAGS = -Wall -Wextra
CFLAGS =  $(CXXFLAGS)
LDFLAGS =

.PHONY: all tests clean

all: vecalc test
test: scalar_test vector_test

VECTOR_OBJ = test_vector.o vector.o
SCALAR_OBJ = test_scalar.o scalar.o vector.o
VECALC_OBJ = vecalc.o  calc_state.o input_state.o vector.o scalar.o
vecalc: $(VECALC_OBJ)
	$(CXX) $(VECALC_OBJ) -o vecalc
vector_test: $(VECTOR_OBJ)
	$(CXX) $(VECTOR_OBJ) -o vector_test
scalar_test: $(SCALAR_OBJ)
	$(CXX) $(SCALAR_OBJ) -o scalar_test

vector.o: vector.cc vector.h
scalar.o: scalar.cc scalar.h vector.h
calc_state.o: calc_state.cc calc_state.h vector.h scalar.h vecalc.h
input_state.o: input_state.cc input_state.h vector.h vecalc.h
test_scalar.o: test_scalar.cc vector.h scalar.h
test_vector.o: test_vector.cc vector.h
vecalc.o: vecalc.h vecalc.cc calc_state.h input_state.h vector.h

clean: 
	rm -f vector.o scalar.o calc_state.o input_state.o test_scalar.o test_vector.o vecalc.o
	rm -f vector_test scalar_test vecalc