CXX = c++
EXE = main
CFLAGS = -std=c++11 -Wall -Wextra
DFLAGS = -D DEBUG
IFLAGS = -I . 

all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)

clean:
	@rm *~ *.o $(EXE)

.PHONY: clean
