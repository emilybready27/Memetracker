EXENAME = main
OBJS = main.o searcher.o avltree.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp avltree.h searcher.h
	$(CXX) $(CXXFLAGS) main.cpp

searcher.o : searcher.cpp searcher.h
	$(CXX) $(CXXFLAGS) searcher.cpp

avltree.o: avltree.h avltree.cpp
	$(CXX) $< $(CXXFLAGS) avltree.cpp

clean :
	-rm -f *.o $(EXENAME)
