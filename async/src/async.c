#include <stdlib.h>
#include "link.h"
#include "async.h"

static void *_async_wrapper(void*);
static int   _async_join(async_t *async);
static _wrapper_data_t *wrapper_data_new(async_t* ,async_f, void*);

/***********************************
*         Wrapper function         *
************************************/

static _wrapper_data_t *wrapper_data_new(async_t *async ,async_f func, void *data) {
    _wrapper_data_t *wrapper_data = (_wrapper_data_t*)malloc(sizeof(_wrapper_data_t));
    if(wrapper_data == NULL)
        return NULL;
        
    wrapper_data->func  = func;
    wrapper_data->data  = data;
    wrapper_data->async = async;
    
    return wrapper_data;
}

/***********************************
*         Async function           *
************************************/

async_t *async_new() {
    async_t *async = (async_t*)malloc(sizeof(async_t));
    if(async == NULL)
        return NULL;
        
    link_t *result = link_new();
    if(link == NULL) {
        free(async);
        return NULL;
    }
    async->_result = result;
    
    link_t *pids = link_new();
    if(link == NULL) {
        free(result);
        free(async);
        return NULL;
    }
    async->_pids = pids;
    
    int ret = pthread_mutex_init(&(link->_lock), NULL);
    if(ret != 0) {
        free(link);
        free(async);
        return NULL;
    }
    
    return async;
}

int async_run(async_t *async ,async_f func, void *data) {    
    pthread_t        pid;
    _wrapper_data_t *wrapper_data = wrapper_data_new(async, func, data)
    int              ret;
    
    ret = pthread_create(&pid, NULL, _async_wrapper, wrapper_data);
    if(ret != 0) {
        return 1;
    } else {
        node_t *node = node_new(&pid);
        link_add(async->_pids, node);
        return 0;
    }
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

static int _async_join(async_t *async) {
    void      **_ret;
    pthread_t *pid;
    int       ret = 0;
    
    if(pid = link_tail(async->_pids) != NULL) {
        ret = pthread_join(*pid, _ret);
        if(ret != 0 )
            ret = 1
    }
    
    return ret;
}

int async_exit(async_t *async) {
    int ret;
    void **_ret;
    
    ret = _async_join(async);
    if(ret != 0)
        return 1;    
    
    ret = pthread_mutex_destroy(async->_lock)
    if(ret != 0)
        return 1;
    
    ret = link_free(async->_result);
    if(ret != 0)
        return 1;
        
    ret = link_free(async->_pids);
    if(ret != 0)
        return 1;
        
    free(async);
    return 0
}

static void *_async_wrapper(void *data) {
    if(data = NULL)
        pthread_exit(NULL);
    
    _wrapper_data_t *wrapper_data = (_wrapper_data_t*)data;
    void ret = (*wrapper_data->func)(wrapper_data->data);
    
    node_t *node = node_new(ret);
    if(node != NULL) {
        link_add(wrapper_data->async->_result, node);
    }
           
    pthread_exit(ret);
}
