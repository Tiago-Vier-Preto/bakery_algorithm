#ifndef LAMPORT_HPP
#define LAMPORT_HPP

void lamport_mutex_init();
void lamport_mutex_lock (int thread_id);
void lamport_mutex_unlock (int thread_id);
static void set_choosing(int index, bool value);
static void set_choosing(int index, bool value);	
static bool get_choosing(int index);
static void set_ticket(int index, int value);
static int get_ticket(int index);
static int get_max_ticket();

#endif 