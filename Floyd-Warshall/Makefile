CXX = c++
EXE = floyd
CFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I ../Graph

all: $(EXE)

$(EXE): $(EXE).cc
	$(CXX) $^ -o $@ $(CFLAGS) $(IFLAGS)

# tarjan.o: tarjan.cc
# 	$(CXX) -c $^ -o $@ $(CFLAGS) $(IFLAGS)



clean:
	@rm *~ *.o $(EXE)

.PHONY: clean
