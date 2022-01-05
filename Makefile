EXE = main
OBJS = main.o
 
CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm
 
all : $(EXE)
 
output_msg: ; $(CLANG_VERSION_MSG)
 
$(EXE) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)
 
#object file dependncies
main.o : main.cpp CSVReader.hpp Graph.cpp Visualization.cpp BFS.cpp Dijkstra.cpp
	$(CXX) $(CXXFLAGS) main.cpp
 
# Custom Clang version enforcement Makefile rule:
# for using 'make test'
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")
 
IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1'. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

test: output_msg cs225/catch/catchmain.cpp tests/test.cpp Dijkstra.cpp BFS.cpp
	$(LD) cs225/catch/catchmain.cpp tests/test.cpp Dijkstra.cpp BFS.cpp $(LDFLAGS) -o test
 
clean:
	-rm -f *.o $(EXE) test