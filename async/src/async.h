#ifndef ASYNC_ASYNC_H_
#define  ASYNC_ASYNC_H_

#include <pthread.h>

typedef void *(*async_f)(void*);
typedef struct node_s node_t;
typedef struct link_s link_t;

typedef struct _wrapper_data_s {
    async_f  func;
    void    *data;
} _wrapper_data_t;

typedef struct async_s {
    pthread_mutex_t  _lock;
    link_t          *_result;
    link_t          *_pids;
} async_t;


async_t *async_new();
int      async_run(async_f, void*);
node_t  *async_ret_head(astnc_t*);
node_t  *async_ret_tail(astnc_t*);
size_t   async_ret_len(astnc_t*);
int      async_destroy(async_t*);

#endif //ASYNC_ASYNC_H_