CXX = c++
EXE = Dijkstra/dijkstra
CFLAGS = -std=c++11 -Wall -Wextra
#DFLAGS = -D DEBUG
IFLAGS = -I ./Heap -I ./Graph
all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)


run:
	./Dijkstra/dijkstra


clean:
	@rm *~

.PHONY: clean
