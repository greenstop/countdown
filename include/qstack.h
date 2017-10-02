#ifndef QUEUESTACKLL_H
#define QUEUESTACKLL_H
#include <linkedlist.h>
typedef struct queuestack QStack;
struct queuestack 
{
    Linkedlist *head;
    Linkedlist *tail;
    void (*init)(QStack*this);
    void (*push)(QStack*this,void*item);
    void *(*pop)(QStack*this);
    void (*enqueue)(QStack*this,void*item);
    void *(*dequeue)(QStack*this);
};
QStack QStackInit();
#endif
