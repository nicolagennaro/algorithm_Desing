CXX = c++
SRC = $(wildcard *.cc)
EXE = $(SRC:.cc=.x)
CFLAGS = -std=c++14 -Wall -Wextra
IFLAGS = -I ./


all: $(EXE)

%.x: %.cc
	$(CXX) $< -o $@ $(CFLAGS) $(IFLAGS)


clean:
	@rm *~ $(EXE)

.PHONY: clean
