CXX = c++
EXE = strassen_less_mem1
CFLAGS = -std=c++11 -Wall -Wextra
#DFLAGS = -D DEBUG_C -D DEBUG_P -D DEBUG_FILL
#DFLAGS = -D DEBUG_S
#DFLAGS = -D DEBUG_FILL
all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(DFLAGS)


clean:
	@rm *~ $(EXE)

.PHONY: clean
