CXX = c++
EXE = select_clean
CFLAGS = -std=c++11 -Wall -Wextra
#DFLAGS = -D DEBUG

all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(DFLAGS)


clean:
	@rm *~ $(EXE)

.PHONY: clean
