#include <stdlib.h>
#include "link.h"
#include "async.h"

static void *_async_wrapper(void*);
static void _async_done();
static _wrapper_data_t *wrapper_data_new(async_f, void*);

/***********************************
*         Wrapper function         *
************************************/

static _wrapper_data_t *wrapper_data_new(async_f func, void *data) {
    
}

/***********************************
*         Async function           *
************************************/

async_t *async_new() {
    async_t *async = (async_t*)malloc(sizeof(async_t));
    if(async == NULL)
        return NULL;
        
    link_t *link = link_new();
    if(link == NULL) {
        free(async);
        return NULL;
    }
    async->_result = link;
    
    int ret = pthread_mutex_init(&(link->_lock), NULL);
    if(ret != 0) {
        free(link);
        free(async);
        return NULL;
    }
    
    return async;
}

int async_run(async_f func, void *data) {    
    pthread_t        pid;
    _wrapper_data_t *wrapper_data = wrapper_data_new(func, data)
    int              ret;
    
    ret = pthread_create(&pid, NULL, _async_wrapper, wrapper_data);
}

node_t *async_ret_head(async_t *async) {
    if(async == NULL)
        return NULL;
    
    return link_head(async->_result)
}

node_t *async_ret_tail(async_t *async) {
    if(async == NULL)
        return NULL;
    
    return link_tail(async->_result)
}

size_t async_ret_len(async_t *async) {
    if(async == NULL)
        return 0;
    
    return link_len(async->_result)
}

int async_destroy(async_t *async) {
    int ret;
    
    ret = pthread_mutex_destroy(async->_lock)
    if(ret != 0)
        return 1;
    
    ret = link_free(async->_result);
    if(ret != 0)
        return 1;
        
    free(async);
    return 0
}

static void *_async_wrapper(void*) {
    
}

static void _async_done() {
    
}