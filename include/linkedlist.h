#ifndef LINKEDLIST_H
#define LINKEDLIST_H
typedef struct linkedlist {
    struct linkedlist *front;
    void *content;
    struct linkedlist *back;
} Linkedlist;
#endif
