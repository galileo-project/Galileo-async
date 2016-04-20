#include <stdlib.h>
#include "link.h"
#include "async.h"

static void    *_async_routine(void*);
static _task_t *task_new(async_f, void*);
static void     _async_ret_add(astnc_t*, void*);

/***********************************
*         Wrapper function         *
************************************/

static _task_t *task_new(async_f, void*) {
    _task_t *task = (_task_t*)malloc(sizeof(_task_t));
    if(task == NULL)
        return NULL;
        
    task->func  = func;
    task->data  = data;
    
    return task;
}

/***********************************
*         Async function           *
************************************/

async_t *async_new(size_t num) {
    int ret;
    async_t *async = (async_t*)malloc(sizeof(async_t));
    if(async == NULL)
        return NULL;
        
    async->_result = link_new();
    if(async->_result == NULL) {
        free(async);
        return NULL;
    }
    
    async->_tasks = link_new();
    if(async->_tasks == NULL) {
        free(result);
        free(async);
        return NULL;
    }
    
    async->_threadid = (pthread_t*)malloc(num * sizeof(pthread_t));
    if(async->_threadid == NULL) {
        free(result);
        free(tasks);
        free(async);
        return NULL;
    }
    
    ret = pthread_mutex_init(&(async->_lock), NULL);
    if(ret != 0) {
        free(task);
        free(result);
        free(async);
        return NULL;
    }
    
    ret = pthread_mutex_init(&(async->_ready), NULL);
    if(ret != 0) {
        free(task);
        free(result);
        free(async);
        pthread_mutex_destroy(&(async->_lock));
        return NULL;
    }
    
    async->_shutdown = 0;
    async->_max_thread_mun = num;
    
    int i;
    for(i = 0; i < num; i++) {
        ret = pthread_create(&(async->_threadid[i]), NULL, _async_routine, async);    
    }
    
    return async;
}

int async_run(async_t *async ,async_f func, void *data) {    
    _task_t *task = task_new(func, data);
    int      ret;
    
    if(task == NULL) {
        return 1;
    }
    
    node_t *node = node_new(task);
    pthread_mutex_lock(&(async->_lock));
    ret = link_add(async->_tasks, node);
    pthread_mutex_unlock(&(async->_lock));
    
    if(ret != 0)
        return 1;
    
    pthread_mutex_signal(&(async->_ready));
    return 0;
}

int async_destroy(async_t *async) {
    if(async->_shutdown)
        return 1;
    async->_shutdown = 1;
        
    pthread_cond_broadcast(&(async->_ready));
    
    int i;
    for(i = 0; i < async->_max_thread_mun; i++)
        pthread_join(&(async->_threadid[i]));
    free(async->_threadid)
    
    ret = pthread_mutex_destroy(&(async->_lock));
    if(ret != 0)
        return 1;
        
    ret = pthread_cond_destroy(&(async->_ready))
    if(ret != 0)
        return 1;
    
    ret = link_free(async->_result);
    if(ret != 0)
        return 1;
        
    ret = link_free(async->_tasks);
    if(ret != 0)
        return 1;
        
    free(async);
    return 0
}

static void *_async_routine(void *arg) {
    async_t *async = (async_t*)arg;
    _task_t *task  = NULL;
    void    *ret   = NULL;  
    
    while(1) {
        pthread_mutex_lock(&(async->_lock));
        if(link_len(async->_tasks) == 0 && !async->_shutdown)
            pthread_cond_wait(&(async->_ready), &(async->_lock));
            
        if(async->_shutdown) {
            pthread_mutex_unlock(&(async->_lock));
            pthread_exit(NULL);
        }
            
         task = link_head(async->_tasks);
        if(task != NULL) {
            ret = (*(task->func))(task->data);
            _async_ret_add(async, ret);  
        }
            
        pthread_mutex_unlock(&(async->_lock));
        free(task);
        task = NULL;
    }
    
    pthread_exit(NULL);
}

/*Async ret link*/
static void _async_ret_add(async_t *async, void *data) {
    node_t *node = node_new(data);
    if(node != NULL) {
        link_add(async->_result, node);
    }
}

node_t *async_ret_head(async_t *async) {
    if(async == NULL)
        return NULL;
    
    node_t *node = link_head(async->_result)
    if(node != NULL)
        return node->data;
    return NULL;
}

node_t *async_ret_tail(async_t *async) {
    if(async == NULL)
        return NULL;
    
    node_t *node = link_tail(async->_result)
    if(node != NULL)
        return node->data;
    return NULL;
}

size_t async_ret_len(async_t *async) {
    if(async == NULL)
        return 0;
    
    return link_len(async->_result)
}
/*Async ret link end*/