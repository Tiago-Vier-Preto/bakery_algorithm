#include <iostream>   
#include "../include/lamport_lib.hpp"

#define MAX_THREADS 100

static int choosing[MAX_THREADS];
static int ticket[MAX_THREADS];

void lamport_mutex_init() {
    for (int i = 0; i < MAX_THREADS; i++) {
        choosing[i] = false;
        ticket[i] = 0;
    }
}

void lamport_mutex_lock (int thread_id) {
    int i = thread_id - 1;
    set_choosing(i, true);
    set_ticket(i, get_max_ticket() + 1);
    set_choosing(i, false);
    for (int j = 0; j < MAX_THREADS; j++) {
        while (get_choosing(j)) {} // do nothing
        while ((get_ticket(j) != 0) && ((get_ticket(j) < get_ticket(i)) || ((get_ticket(j) == get_ticket(i)) && (j < i)))) {} // do nothing
    }
}

void lamport_mutex_unlock (int thread_id){
    set_ticket(thread_id - 1, 0);
}

static int get_max_ticket() {
    int max = ticket[0];
    for (int i = 1; i < MAX_THREADS; i++) 
        max = ticket[i] > max ? ticket[i] : max;
    return max;
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