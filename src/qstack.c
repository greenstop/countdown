#include <qstack.h>
#include <stdlib.h>

/* return NULLified linkedlist node
 */
Linkedlist *listInit(void *item) 
{
    Linkedlist *list = (Linkedlist*) malloc(sizeof(Linkedlist));
    list->front = NULL;
    list->back = NULL;
    list->content = item;
    return list;
}

/* initialize qstack
 * assign methods
 */
void __QStack_init(QStack *this) 
{
    this->head = NULL;
    this->tail = NULL;
}

/* push items
 */
void __QStack_push(QStack *this, void *item) 
{
    Linkedlist *list = listInit(item);
    if (this->head != NULL) {
        list->back = this->head;
        this->head = list;
        list->back->front = list;
    } else {
        this->head = list;
        this->tail = list;
    }
}

/* pop items
 */
void *__QStack_pop(QStack *this) 
{
    void *item = NULL;  
    Linkedlist *head = this->head;
    if (this->head != NULL) {
        item = this->head->content;
        this->head = this->head->back;
        if (this->head == NULL)
            this->tail = NULL;
        else this->head->front = NULL;
    }
    free(head);
    return item;
}

/* enqueue
 */
void __QStack_enqueue(QStack *this, void *item) 
{
    this->push(this,item);
}

/* dequeque
 */
void *__QStack_dequeue(QStack *this) 
{
    void *item = NULL;  
    Linkedlist *tail = this->tail;
    if (this->tail != NULL) {
        item = this->tail->content;
        this->tail = this->tail->front;
        if (this->tail == NULL)
            this->head = NULL;
        else this->tail->back = NULL;
    }
    free(tail);
    return item;
}

/* return a new qstack, assign methods
 */
QStack QStackInit() 
{
    QStack s;
    s.head = NULL;
    s.tail = NULL;
    s.init = __QStack_init;
    s.push = __QStack_push;
    s.pop = __QStack_pop;
    s.enqueue = __QStack_enqueue;
    s.dequeue = __QStack_dequeue;
    return s;
}
