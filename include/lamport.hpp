#ifndef LAMPORT_HPP
#define LAMPORT_HPP

void lamport_mutex_init();
void lamport_mutex_lock (int thread_id);
void lamport_mutex_unlock (int thread_id);

#endif 