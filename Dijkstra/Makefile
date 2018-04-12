CXX = c++
EXE = Astar
CFLAGS = -std=c++11 -Wall -Wextra
#DFLAGS = -D DEBUG
IFLAGS = -I ../Graph -I ../Heap


all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)

collapse: collapse.cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)


clean:
	@rm *~ $(EXE)

.PHONY: clean
