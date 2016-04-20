#ifndef ASYNC_LINK_H_
#define  ASYNC_LINK_H_

typedef struct node_s {
    struct node_s *pre;
    struct node_s *next;
    void          *data;
} node_t;

node_t *node_new(void*);
node_t *node_next(node_t*);

typedef struct link_s {
    node_t *header;
    node_t *tail;
    size_t  len;
} link_t;

link_t *link_new();
int     link_add(link_t*, node_t*);
size_t  link_len(link_t*);
node_t *link_head(link_t*);
node_t *link_tail(link_t*);
int     link_free(link_t*);

#endif //ASYNC_LINK_H_