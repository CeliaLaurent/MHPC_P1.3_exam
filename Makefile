SRC = main.cpp  
HEADERS= bst.hpp 

CXX = c++
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

format: $(SRC) $(HEADERS) bst.cpp
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this command"

.PHONY: format

clean:
	rm -f $(EXE) *~ *.o

.PHONY: clean

main.o: bst.hpp
main.x: bst.o
bst.o: bst.hpp
