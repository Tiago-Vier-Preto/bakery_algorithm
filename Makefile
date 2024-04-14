SRC = $(wildcard ./src/*.cpp)
BIN = $(patsubst ./src/%.cpp, ./bin/%.exe, $(SRC))

CXX = g++

all: $(BIN)

./bin/%.exe: ./src/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $< -o $@
	
clean:
	@echo "Cleaning up..."
	@rm -f $(BIN)
