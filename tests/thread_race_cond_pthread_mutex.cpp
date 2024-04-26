#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define num_threads 3

int shared_var = 0;
int num_rep = 3000000;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Inicialização do mutex

struct thread_info {
    pthread_t id;
    int num;
};

static void *thread_start(void *arg)
{
    struct thread_info *tinfo = static_cast<struct thread_info *>(arg);

    printf("Hello! I'm thread %d, id %lu!\n", tinfo->num, tinfo->id);
    for (int i = 0; i < num_rep; i++) {
        pthread_mutex_lock(&mutex); // Bloqueia o mutex antes de acessar a variável compartilhada
        shared_var = shared_var + 1;
        pthread_mutex_unlock(&mutex); // Desbloqueia o mutex após a atualização da variável compartilhada
    }

    return NULL;
}

int main(int argc, char **argv)
{
    int thread_num, ret;
    struct thread_info tinfo[num_threads];
    pthread_attr_t attr;
    void *res;

    if (argc > 1)
        num_rep = strtol(argv[1], NULL, 10);

    ret = pthread_attr_init(&attr);
    if (ret != 0)
        handle_error_en(ret, "pthread_attr_init");

    for (thread_num = 0; thread_num < num_threads; thread_num++) {
        tinfo[thread_num].num = thread_num + 1;

        ret = pthread_create(&tinfo[thread_num].id, &attr, &thread_start, &tinfo[thread_num]);
        if (ret != 0)
            handle_error_en(ret, "pthread_create");
    }

    ret = pthread_attr_destroy(&attr);
    if (ret != 0)
        handle_error_en(ret, "pthread_attr_destroy");

    for (thread_num = 0; thread_num < num_threads; thread_num++) {
        ret = pthread_join(tinfo[thread_num].id, &res);
        if (ret != 0)
            handle_error_en(ret, "pthread_join");

        printf("Joined with thread %d, id %lu\n", tinfo[thread_num].num, tinfo[thread_num].id);
    }
    printf("Global var: %d\n", shared_var);

    exit(EXIT_SUCCESS);
}
