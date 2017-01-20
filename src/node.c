#include <stdio.h>
#include <node.h>

int goal = 801;

/* exit gracefully
 */
void exitError(int action, char *s) 
{
    switch(action) {
        case 404:
            fprintf( stderr, "Error %d:\nSome pointers are null.\n%s", action, s);
            break;
        case 503:
            fprintf( stderr, "Error %d:\nInternal Error.\n%s", action, s);
            break;
        case 509:
            fprintf( stderr, "Error %d:\nLimit Exceeded.\n%s", action, s);
            break;
        case 200:
            fprintf( stderr, "Error %d:\nNormal Exit.\n%s", action, s);
            break;
        default: 
            fprintf( stderr, "Error %d:\nSomething went wrong.\n%s", action, s);
    }
    exit( action);
}

/* talloc: make a node
 */
struct node *nalloc()
{
    struct node *p;
    p = (struct node *) malloc(sizeof(struct node));
    if( p == NULL) return NULL; //no memory
    
    //Nullify fields
    //p->path = NULL;
    p->numbers = NULL;
    p->total = 0;

    //assign 100byte char array to path
    //  used malloc for persistence
    //p->path = ( char *) calloc( 100, sizeof(char)); 
    
    return p;
}

/* Create space for a numNode node
 */
struct numNode *numNodealloc()
{
    struct numNode *p;
    p = (struct numNode *) malloc(sizeof(struct numNode));
    if( p == NULL) return NULL; //no memory

    //Nullify fields
    p->number = 0;
    p->back = NULL;
    p->front = NULL;
    
    return p;
}

/* Conduct a goal test
 */
bool goalTest( struct node *p, struct numNode *n, char action)
{
    if( p == NULL || n == NULL || action == '\0') exitError(404,"goalTest");
    
    /* calculate with p->total
     */
    switch(action) {
        case '+':
            p->total += n->number;
            break;
        case '-':
            p->total -= n->number;
            break;
        case '*':
            p->total *= n->number;
            break;
        case '/':
            if( n->number == 0) return false;
            if (n->number != 0) p->total /= n->number;
            break;
    }

    /* add n->number and action to p->path
     */
    //char path[10];
    //sprintf(path, "%c%0.2f", action, n->number);
    //strcat(p->path,path);
    //assert(p->path[0] != '\0');

    return p->total == goal;
}

/* return what goal is set to
 */
int getGoal() 
{
    return goal;   
}

/* Set Goal.
 */
void setGoal(int goalee) 
{
    goal = goalee;
    assert( goal == goalee );
}

/* return linked list with given node delinked
 */
struct numNode * numNodeDelinker(struct numNode *p)
{
    // flag bits structure, to note Null pointers
    struct {
        unsigned int haveFront : 1; // specify width of 1 bit
        unsigned int haveBack : 1;
    } flags; // struct with 2 1-bit fields

    //mark front and back ends of linkedlist node
    struct numNode *back, *front;
    back = p->back;
    front = p->front;

    //NULL the links in the given node
    p->back = NULL;
    p->front = NULL;

    //set bits
    if( back == NULL) flags.haveBack = 0;
    else flags.haveBack = 1;
    if( front == NULL) flags.haveFront = 0;
    else flags.haveFront = 1;

    //decision tree
    //No links
    if( flags.haveFront == 0 && flags.haveBack == 0) {
        return NULL;
    }
    //Is the root, sever root
    else if( flags.haveFront == 0 && flags.haveBack == 1) {
        back->front = NULL; //free severed node somewhere
        return back;
    }
    //Is last, sever last
    else if( flags.haveFront == 1 && flags.haveBack == 0) {
        front->back = NULL;
        return front;
    }
    //In middle, swap
    else if( flags.haveFront == 1 && flags.haveBack == 1) {
        back->front = front;
        front->back = back;
        return front;
    }
    return NULL;
}

/* make number linked list from numbers
 */
struct numNode * numLinkFromArray( int *nSeq, int nSize) 
{
    // create initial node
    struct numNode *root = numNodealloc();
    if ( root == NULL) exitError(404,"numLinkFromArray");
    root->number = *nSeq;
    nSeq++;

    struct numNode *p;
    int i;
    for( p=root, i=0; i < (nSize-1); p=p->back, i++, nSeq++) {
        p->back = numNodealloc();
        if ( p->back == NULL) exitError(404,"numLinkFromArray");
        p->back->number = *nSeq;
        p->back->front = p;
    }
    
    return root;
}

/* take root and destroy (free) each numNode
 */
bool numNLinkDestroyer( struct numNode *root) 
{
    if( root == NULL) return false;
    struct numNode *p, *q;
    int i;
    for( p=root, i=0; p != NULL; p=q, i++) {
        q = p->back;
        free(p);
    }
    return true;
}

/* return the root of a node
 */
struct numNode * rootOfNode( struct numNode *node) 
{
    if( node == NULL) exitError(404,"rootOfNode");
    while( node->front != NULL)
        node = node->front;
    return node;
}

/* free the allocated memory of the struct node
 * and the allocated char array pointed to
 * within the struct
 */
void freeNode( struct node *node) 
{
    //char *path = node->path;
    numNLinkDestroyer( node->numbers);
    free( node);
    //free( path);
}

/* With the given node return new allocated
 * node with a subset of the bigger set
 * of the given node.
 */
bool newNodeSubsetNumbers(
    struct node *newNode,
    struct node *node,
    struct numNode *numToBeExtracted) 
{
    //exit if null
    if( node == NULL)
        exitError(404, "newNodeSubsetNumbers node null");
    if( numToBeExtracted == NULL)
        exitError(404, "newNodeSubsetNumbers numNode to extract null");
    
    //get root, new root
    struct numNode *root = rootOfNode( numToBeExtracted);
    
    //copy to new allocated space
    struct numNode *p = NULL, *q = NULL, *r = NULL;
    for( p=root; p != NULL; p=p->back) {
        if( p == numToBeExtracted) continue;
        q = numNodealloc();
        q->number = p->number;
        if( r != NULL) {
            q->front = r;
            r->back = q;
        }
        r = q;
    }
    if( q == NULL) return false;

    //allocate new node with newly allocated link list
    //newNode = nalloc(); //changing address of passed pointer doesn't persist
    //printf("Pointer address in f()::%p\n", newNode);
    newNode->total = node->total;
    newNode->numbers = rootOfNode( q);
    if( newNode == NULL)
        exitError(404, "newNodeSubsetNumbers new node null");
    if( newNode->numbers == NULL)
        exitError(404, "newNodeSubsetNumbers new node numbers null");

    return true;
}
