SRC = $(wildcard ./src/*.cpp)
BIN = $(patsubst ./src/%.cpp, ./bin/%.exe, $(SRC))

CXX = g++

all: bin_dir $(BIN)

./bin/%.exe: ./src/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $< -o $@
	
clean:
	@echo "Cleaning up..."
	@rm -rf ./bin

bin_dir:
	@mkdir -p ./bin