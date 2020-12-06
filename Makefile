EXENAME = main
<<<<<<< HEAD
OBJS = main.o
=======
OBJS = main.o searcher.o avltree.o
>>>>>>> fdef20ac42233f6cd1adbbf2d605133b852787bd

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

<<<<<<< HEAD
main.o: main.cpp avltree.h avltree.cpp
	$(CXX) $< $(CXXFLAGS)
	
# avltree.o: avltree.h avltree.cpp
# 	$(CXX) $< $(CXXFLAGS)
=======
avltree.o: avltree.h avltree.cpp
	$(CXX) $< $(CXXFLAGS) avltree.cpp
>>>>>>> fdef20ac42233f6cd1adbbf2d605133b852787bd

clean :
	-rm -f *.o $(EXENAME)
