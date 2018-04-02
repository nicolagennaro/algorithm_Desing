CXX = c++
EXE = fischer-mayer
CFLAGS = -std=c++11 -Wall -Wextra
#DFLAGS = -D DEBUG
IFLAGS = -I ../Graph 


all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)


clean:
	@rm *~ $(EXE)

.PHONY: clean
