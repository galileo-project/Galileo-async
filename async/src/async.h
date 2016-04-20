#ifndef ASYNC_ASYNC_H_
#define  ASYNC_ASYNC_H_

#include <pthread.h>

typedef void *(*async_f)(void*);
typedef struct node_s node_t;
typedef struct link_s link_t;
typedef struct async_s async_t;

typedef struct _task_s {
    async_f  func;
    void    *data;
} _task_t;

typedef struct async_s {
    pthread_mutex_t  _lock;
    pthread_cond_t   _ready;
    pthread_t       *_threadid;
    link_t          *_result;
    link_t          *_tasks;
    int              _shutdown;
    size_t           _max_thread_mun;
} async_t;


async_t    *async_new(size_t);
int         async_run(async_t*, async_f, void*);
int         async_destroy(async_t*);

node_t     *async_ret_head(async_t*);
node_t     *async_ret_tail(async_t*);
size_t      async_ret_len(async_t*);

#endif //ASYNC_ASYNC_H_