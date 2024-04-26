LIB = $(wildcard ./lib/*.cpp)
OBJ = $(patsubst ./lib/%.cpp, ./build/%.o, $(LIB))

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

lamport_test: build
	@echo "Running test with lamport mutex algorithm..."
	@$(CXX) ./tests/thread_race_cond_lamport.cpp -o lamport_test.exe -llamport -L./build -lpthread
	@LD_LIBRARY_PATH=./build ./lamport_test.exe 		

pthread_mutex_test: build
	@echo "Running test with POSIX pthreads API..."
	@$(CXX) ./tests/thread_race_cond_pthread_mutex.cpp -o pthread_mutex_test.exe -lpthread
	@./pthread_mutex_test.exe 											

clean:
	@echo "Cleaning up..."
	@rm -f ./*.exe
	@rm -f ./*.sh
	@rm -rf ./build

compare: lamport_test.exe pthread_mutex_test.exe
	@echo '#!/bin/bash' > compare_time_execution.sh
	@echo 'echo 'Execution time for Lamport Mutex Algorithm:'' >> compare_time_execution.sh
	@echo 'time LD_LIBRARY_PATH=./build ./lamport_test.exe > /dev/null 2>&1' >> compare_time_execution.sh
	@echo 'echo ''' >> compare_time_execution.sh
	@echo 'echo 'Execution time for POSIX pthreads API:'' >> compare_time_execution.sh
	@echo 'time ./pthread_mutex_test.exe > /dev/null 2>&1' >> compare_time_execution.sh
	@echo 'echo ''' >> compare_time_execution.sh
	@chmod +x compare_time_execution.sh
	@./compare_time_execution.sh
	@rm compare_time_execution.sh




