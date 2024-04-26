#include <iostream>
#include <vector>   
#include "../include/lamport_lib.hpp"

#define MAX_THREADS 100

static std::vector<bool> choosing(1, false);
static std::vector<int> ticket(1, 0);

void lamport_mutex_init() {
    choosing.resize(MAX_THREADS, false); 
    ticket.resize(MAX_THREADS, 0); 
}

void lamport_mutex_lock (int thread_id) {
    set_choosing(thread_id - 1, true);
    set_ticket(thread_id - 1, get_max_ticket() + 1);
    set_choosing(thread_id - 1, false);
    for (int j = 0; j < MAX_THREADS; j++) {
        while (get_choosing(j)) {} // do nothing
        while ((get_ticket(j) != 0) && ((get_ticket(j) < get_ticket(thread_id - 1)) || ((get_ticket(j) == get_ticket(thread_id - 1)) && (j < thread_id - 1)))) {} // do nothing
    }
}

void lamport_mutex_unlock (int thread_id){
    set_ticket(thread_id - 1, 0);
}

// Getters and setters
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
    for (int i = 1; i < MAX_THREADS; i++) 
        max = ticket[i] > max ? ticket[i] : max;
    return max;
}