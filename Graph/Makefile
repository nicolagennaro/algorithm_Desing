CXX = c++
EXE = testGraph_struct
CFLAGS = -std=c++11 -Wall -Wextra
#DFLAGS = -D DEBUG
IFLAGS = -I ../Heap -I ./

all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)

clean:
	@rm *~

.PHONY: clean
