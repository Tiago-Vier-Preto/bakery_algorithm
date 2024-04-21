#ifndef LAMPORT_HPP
#define LAMPORT_HPP

#include <vector>

void lamport_mutex_init(int num_threads);
void lamport_mutex_lock (int thread_id);
void lamport_mutex_unlock (int thread_id);
static int get_num_threads();
static void set_num_threads(int num_threads);
static void set_choosing(int index, bool value);
static void set_choosing(int index, bool value);	
static bool get_choosing(int index);
static void set_ticket(int index, int value);
static int get_ticket(int index);
static int get_max_ticket();

#endif 