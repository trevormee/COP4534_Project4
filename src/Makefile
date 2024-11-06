CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJS = main.o BinPacking.o

proj4 : ${OBJS}
		${CXX} $(CXXFLAGS) -o $@ ${OBJS}

 
main.o : BinPacking.hpp
BinPacking.o : BinPacking.hpp

clean :
		rm ${OBJS}