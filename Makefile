EXENAME = main
OBJS = main.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

main.o: main.cpp avltree.h avltree.cpp
	$(CXX) $< $(CXXFLAGS)
	
# avltree.o: avltree.h avltree.cpp
# 	$(CXX) $< $(CXXFLAGS)

clean:
	-rm -f *.o $(EXENAME)
