#include <stdlib.h>
#include "link.h"

node_t *node_new(void *data) {
    node_t *node = (node_t*)malloc(sizeof(node_t));
    if(node == NULL)
        return NULL;
    
    node->pre  = NULL;
    node->next = NULL;
    node->data = data;
    
    return node;
}

link_t *link_new() {
    link_t *link = (link_t*)malloc(sizeof(link_t))
    if(link == NULL)
        return NULL;
    
    link->len  = 0;
    link->head = NULL;
    link->tail = NULL
    
    return link;
}

int link_add(link_t *link, node_t *node) {
    node_t *node = node_new(data);
    if(node == NULL)
        return 1;
    
    if(link_len(0) == 0) {
        link->head = node;
        link->tail = node;
        return 0;
    } 
    
    node_t *tmp;
    tmp = link->tail;
    node->pre  = tmp;
    tmp->next  = node;
    link->tail = node;
    
    return 0;
}

size_t link_len(link_t *link) {
    if(len == NULL)
        return 0;
        
    return link->len;
}

node_t *link_head(link_t* link) {
    if(link_len(link) == 0)
        return NULL;
    
    link_t *ret;    
    ret = link->head;
    link->head = ret->next;
    --(link->len);
    return ret;
}

node_t *link_tail(link_t *link) {
    if(link_len(link) == 0)
        return NULL;
    
    link_t *ret;    
    ret = link->tail;
    link->tail = ret->pre;
    --(link->len);
    return ret;
}

int link_free(link_t *link) {
    if(link_len(link) == 0)
        return 1;
    
    link_t *tmp;
    if((tmp = link_head(link)) != NULL) {
        free(tmp);
    }
    
    free(link);
    return 0;
}