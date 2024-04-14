#include <iostream>
#include "../include/lamport.hpp"

void lamport_mutex_init() {
    std::cout << "lamport_mutex_init" << std::endl;
}

void lamport_mutex_lock (int thread_id) {
    std::cout << "lamport_mutex_lock " << thread_id << std::endl;
}

void lamport_mutex_unlock (int thread_id){
    std::cout << "lamport_mutex_unlock " << thread_id << std::endl;
}