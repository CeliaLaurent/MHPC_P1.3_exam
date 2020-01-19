SRC = main.cpp   
HEADERS= node.hpp  iterator.hpp  bst.hpp 

CXX =  c++
CXXFLAGS =  -Wall -Wextra -O3 -std=c++14


EXE = $(SRC:.cpp=.x)


# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o 

all: $(EXE)

.PHONY: all



%.o: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) -c

%.x: %.o
	$(CXX) $^ -o $@

format: $(SRC) $(HEADERS) bst.tpp
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command"

.PHONY: format

clean:
	rm -f $(EXE) *~ *.o

.PHONY: clean

valgrind :
	@$(MAKE) && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXE)

.PHONY: valgrind

run :
	@$(MAKE) &&  ./$(EXE)

.PHONY: valgrind
main.o: node.hpp iterator.hpp bst.hpp
main.x: 


