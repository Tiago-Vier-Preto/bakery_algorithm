#include <iostream>
#include <vector>   
#include "../include/lamport_lib.hpp"

static int num_threads;
static std::vector<bool> choosing;
static std::vector<int> ticket;

void lamport_mutex_init(int n_thread) {
    set_num_threads(n_thread);
    choosing.resize(n_thread); 
    ticket.resize(n_thread); 

    for (int i = 0; i < n_thread; i++) {
        choosing[i] = false;
        ticket[i] = 0;
    }

}

void lamport_mutex_lock (int thread_id) {
    set_choosing(thread_id - 1, true);
    set_ticket(thread_id - 1, get_max_ticket() + 1);
    set_choosing(thread_id - 1, false);
    for (int j = 0; j < get_num_threads(); j++) {
        while (get_choosing(j)) {} // do nothing
        while ((get_ticket(j) != 0) && ((get_ticket(j) < get_ticket(thread_id - 1)) || ((get_ticket(j) == get_ticket(thread_id - 1)) && (j < thread_id - 1)))) {} // do nothing
    }
}

void lamport_mutex_unlock (int thread_id){
    set_ticket(thread_id - 1, 0);
}

// Getters and setters
static int get_num_threads() {
    return num_threads;
}

static void set_num_threads(int n_threads) {
    if (n_threads < 1)
        throw std::invalid_argument("Number of threads must be greater than 0");
    else
        num_threads = n_threads;
}

static void set_choosing(int index, bool value) {
    choosing[index] = value;
}

static bool get_choosing(int index) {
    return choosing[index];
}

static void set_ticket(int index, int value) {
    ticket[index] = value;
}

static int get_ticket(int index) {
    return ticket[index];
}

static int get_max_ticket() {
    int max = ticket[0];
    for (int i = 1; i < get_num_threads(); i++) {
        if (ticket[i] > max)
            max = ticket[i];
    }
    return max;
}