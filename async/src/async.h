#ifndef ASYNC_ASYNC_H_
#define  ASYNC_ASYNC_H_

#include <pthread.h>

typedef void *(*async_f)(void*);
typedef struct node_s node_t;
typedef struct link_s link_t;
typedef struct async_s async_t;

typedef struct _wrapper_data_s {
    async_f  func;
    void    *data;
    async_t *async;
} _wrapper_data_t;

typedef struct async_s {
    pthread_mutex_t  _lock;
    link_t          *_result;
    link_t          *_pids;
} async_t;


async_t    *async_new();
int         async_run(async_t*, async_f, void*);
int         async_exit(async_t*);

pthread_t  *async_pids_head(astnc_t*);
pthread_t  *async_pids_tail(astnc_t*);
size_t      async_pids_len(astnc_t*);

node_t     *async_ret_head(astnc_t*);
node_t     *async_ret_tail(astnc_t*);
size_t      async_ret_len(astnc_t*);

#endif //ASYNC_ASYNC_H_