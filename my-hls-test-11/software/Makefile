CC=g++
CFLAGS=-O3 -fPIC -std=c++11 -fno-gnu-unique
INCFLAGS=-I../firmware/ap_types/

ap_types_test.out: ap_types_test.cpp
	${CC} ${CFLAGS} $< -o $@ ${INCFLAGS}
