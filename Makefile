LIB = $(wildcard ./lib/*.cpp)
OBJ = $(patsubst ./lib/%.cpp, ./build/%.o, $(LIB))

current_dir = $(shell pwd)

SHARED_LIB_FLAG = -shared
CXX = g++


ifeq ($(OS),Windows_NT)
    # Comandos de compilação para Windows
    SHARED_LIB_EXT = dll
else
    # Comandos de compilação para Linux
    SHARED_LIB_EXT = so
endif


build: $(OBJ) 
	@echo "Building..."
	@$(CXX) -o ./build/liblamport.$(SHARED_LIB_EXT) $^ $(SHARED_LIB_FLAG)


$(OBJ): $(LIB) 
	@mkdir -p ./build
	@$(CXX) -c $< -o $@ -fPIC

test1: build
	@echo "Running test 1..."
	@$(CXX) ./tests/thread_race_cond.cpp -o test1.exe -llamport -L./build -lpthread
	@LD_LIBRARY_PATH=$(current_dir)/build ./test1.exe 	# Only works when you are running make from the Makefile's current directory												

clean:
	@echo "Cleaning up..."
	@rm -f ./*.exe
	@rm -rf ./build
