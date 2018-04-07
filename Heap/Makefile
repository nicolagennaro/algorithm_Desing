CXX = c++
EXE = test_Heap_casag
CFLAGS = -std=c++14 -Wall -Wextra
#DFLAGS = -D DEBUG
IFLAGS = -I . 

all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)

BinaryHeap: BinaryHeap.cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)

clean:
	@rm *~ *.o $(EXE)

.PHONY: clean
