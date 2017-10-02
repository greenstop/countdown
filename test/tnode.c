#include <countdown.h>
#include <node.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


/* test null to null assignment
 */
void testNullAssignment() 
{
    /* assigning NULL to NULL causes SIGSEGV error
     * the linkedlist delinker could be
     * simplified to merely
     *   back->front = front
     *   front->back = back
     * for cover all 4 scenerios of front
     * and back being NULL
     */
    struct numNode *r = NULL, *q = NULL;
    assert( r == NULL);
    assert( q == NULL);

    //r->front = q;
    
    assert( r == NULL);
    assert( q == NULL);
    //assert( r->front == NULL);
}

/* test node inside a function without malloc
 */
void testNodeLocal() 
{
    struct node p;
    p.total = 34;
    assert( p.total == 34);
}

/* Test number linked list maker from int array
 */
void testNumLinkMaker() 
{
    //create number seq input
    int nseq[] = {75, 25, 4 ,9, 10, 5};
    int nSize = sizeof(nseq)/sizeof(int);
    assert( nseq[2] ==4);
    assert( nSize == 6);
    
    //initialize
    struct numNode *root = NULL;
    root = numLinkFromArray( nseq, nSize);
    assert( root != NULL);

    //cycle through and assert
    int i;
    int iterations = 0;
    struct numNode *p;
    for( p=root, i=0; p != NULL; p=p->back, i++) {
        assert( i < nSize);
        assert( p->number == nseq[i]);
        iterations++;
    }
    assert( iterations == nSize);

    //go reverse
    struct numNode *lastNode;
    for( p=root; p != NULL; p=p->back)
        lastNode = p;
    assert( lastNode->number == 5);
    iterations=0;
    for( p=lastNode, i=5; p != NULL; p=p->front, i--) {
        assert( i >= 0);
        assert( p->number == nseq[i]);
        iterations++;
    }
    assert( iterations == 6);

    //free linked nodes
    numNLinkDestroyer(root);
}

/* test making new nodes
 */
void testNewNode() 
{
    /* make node
     */
    struct node *pn = nalloc();
    assert(pn->total == 0);
    //assert(pn->path[0] == '\0');
    assert(pn->numbers == NULL);
    //printf(":%lu", sizeof( pn->path));
    
    /* linked number chain, make root
     */
    struct numNode *root = numNodealloc();
    assert( root != NULL);
    root->number = 47;
    assert(root->number == 47);

    /* add links to chain
     */
    struct numNode *p;
    int i;
    for( p=root, i=0; i<10; p=p->back, i++) {
        p->back = numNodealloc();
        assert( p->back != NULL);
        p->back->number = i+1;
        assert( p->back->number == i+1);
    }

    pn->numbers = root;
    assert( pn->numbers->number == 47);

    for(p=pn->numbers, i=0; i<10; p=p->back, i++) {
        //printf("%d) n:%.1f\n", i, p->number);
        if( i==0 ) assert( p->number == 47);
        else assert( p->number == i);
        assert( p->back->number == i+1);
    }

    //numNLinkDestroyer(root);
    freeNode(pn);
}

/* test numAlloc()
 */
void testNumAlloc() 
{
    struct numNode *p; 
    //printf("Pointers: %p, %p", p, q);
    //assert(p == NULL);
    p = numNodealloc();
    assert(p != NULL);

    double d = 47.0;
    p->number = d;
    assert(p->number == 47.0);
    
    free(p);
}

/* test nalloc()
 */
void testnAlloc() 
{
    //create pointer to node allocation
    struct node *p; 
    //assert(p == NULL);
    p = nalloc();
    assert(p != NULL);

    //check if total works as it should
    double d = 45.0;
    p->total = d;
    assert(p->total == 45.0);

    //concatenate some string to path
    //char s[]="0+3+4+3";
    //assert(s[1] == '+');
    //for(i=0; i<10; i++) {
    //    printf("::0path %x :: %c\n", p->path[i], p->path[i]);
    //}
    //strcat( p->path, s);
    //int i;
    //for(i=0; i<10; i++) {
    //    printf(":path %x :: %c\n", p->path[i], p->path[i]);
    //}
    //assert(p->path[1] == '+');
    //assert(p->path[0] != '\0');
    
    freeNode(p);
}

/* test get root of link
 */
void testGetRoot() 
{
    //creat int list
    int seq[] = {43,41,41,33,9};
    struct numNode *p, *q;
    assert( ARRAY_SIZE(seq) == 5);

    //make into linked list
    p = numLinkFromArray( seq, ARRAY_SIZE( seq));
    
    //get 4th node
    p=p->back->back->back;
    assert( p->number == 33);

    //walk back to root
    q = rootOfNode( p);
    assert( q->number == 43);

    //free allocated memory from occupied registry
    //  with given root
    numNLinkDestroyer( q);
}

/* test delink a node from a linked list
 */
void testDelinker() 
{
    //create linked list
    int seq[] = {43,41,41,33,9};
    struct numNode *root, *p, *q; 
    root = numLinkFromArray( seq, ARRAY_SIZE( seq));
    assert( root->number == 43);
    p = root;

    p=p->back->back->back; //node 33
    assert( p->number == 33);

    //remove node
    q = numNodeDelinker( p);
    assert( p->front == NULL);
    assert( p->back == NULL);

    //check
    int i;
    int seq_less[] = {43,41,41,9}; //the correct list
    q = rootOfNode( q);
    for(i=0; i < ARRAY_SIZE( seq_less) ; i++, q=q->back) {
        assert( q->number == seq_less[i]);
        //printf("%d, %.1f\n", seq_less[i], q->number);
    }

    //free
    numNLinkDestroyer(root);
    free(p);
}

/* test goalTest
 */
void testGoalTest() 
{
    //initialize
    char actions[] = {'+','-','*','/'};
    struct node *n = nalloc();
    struct numNode *root = numNodealloc();
    char op = '+';
    bool result;

    //a test round
    n->total = 100;
    root->number = 47;
    setGoal( 147);
    assert( getGoal() == 147);
    //process action and goal test
    result = goalTest( n, root, op);
    assert( result);
    assert( n->total == 147);

    //a test round
    n->total = 100;
    root->number = 48;
    setGoal( 147);
    assert( getGoal() == 147);
    //process action and goal test
    result = goalTest( n, root, op);
    assert( !result);
    assert( n->total == (100 + 48));

    //a test round
    n->total = 100;
    root->number = 48;
    op = '/';
    setGoal( 147);
    assert( getGoal() == 147);
    //process action and goal test
    result = goalTest( n, root, op);
    assert( !result);
    assert( n->total == (100.0 / 48.0));

    //a test round
    n->total = 100;
    root->number = 48;
    op = '*';
    setGoal( 147);
    assert( getGoal() == 147);
    //process action and goal test
    result = goalTest( n, root, op);
    assert( !result);
    assert( n->total == (100.0 * 48.0));
    
    //a test round
    n->total = 100;
    root->number = 0;
    op = '/';
    setGoal( 147);
    assert( getGoal() == 147);
    //process action and goal test
    result = goalTest( n, root, op);
    assert( !result);
    assert( n->total == 100.0);

    //a test round
    n->total = 450;
    root->number = 100;
    op = actions[1];
    setGoal( 350);
    assert( getGoal() == 350);
    //process action and goal test
    result = goalTest( n, root, op);
    assert( result);
    assert( n->total == (450.0 - 100.0));

    //a test round
    n->total = 10;
    root->number = 100;
    op = actions[1];
    setGoal( 350);
    assert( getGoal() == 350);
    //process action and goal test
    result = goalTest( n, root, op);
    assert( !result);
    assert( n->total == (10.0 - 100.0));

    //free
    freeNode( n);
    free( root);
}

/* test goalTest
 */
void teststdbool() 
{
    //try making a custom boolean construct
    typedef struct oneBit {
        unsigned int value : 1;
    } boolean;
    boolean isTrue = {1}; //initialize
    assert( isTrue.value);
    
    //Works but is undefined behavior
    //  (omitting the '.value' suffix)
    //assert( isTrue);
    //printf("1a. bool is %d\n", isTrue);
    //isTrue.value = 0;
    //printf("1b. bool is %d\n", isTrue);

    //use type bool and true and false
    //  definitions in stdbool.h
    bool is = true;
    assert( is);
    is = false;
    assert( !is);

    bool *b;
    b = &is;
    assert( !*b);
    is = true;
    assert( *b);
}

/* test sprintf
 */
void testsprintf() 
{
    char s[10];
    sprintf(s, "%d+%d", 10, 47); //add 5 chars
    assert( s[5] == '\0');

    //printf("s char array::%s::", s);

    //int i;
    //for(i=0; i<ARRAY_SIZE( s)+1; i++) {
        //printf("%d:%x\n", i, s[i]);
    //}
    
    //do a string concatenation
    char r[] = "pad";
    strcat( s, r);
    //printf("s char array::%s::", s);
    assert( s[8] == '\0');

    //give sprintf a pointer instead of
    //  an allocated array
    //Result: SIGSERV ERROR
    //char *t;
    //sprintf(t, "%d+%d", 12, 49); //add 5 chars
    //printf("t char array::%s::", t);
}

/* test getGoal
 */
void testGetGoal() 
{
    setGoal(4747);
    //printf( "goal:: %d", getGoal());
    assert( getGoal() == 4747);
}

/* copy node and a subset of its linked list in new allocation  
 */
void testNewNodeSubsetNum() 
{
    //setup and initialize
    //create num linked list
    int seq[] = {33,34,35,36,37,38};
    struct numNode
        *p,
        *numToExtract = NULL,
        *root = numLinkFromArray( seq, ARRAY_SIZE(seq));
    assert( root->number == 33);
    assert( root->back->number == 34);
    numToExtract = root->back->back;
    assert( numToExtract->number == 35);
    //create node, attach list
    struct node
        *newNode = nalloc(), //must allocate first
        *node = nalloc(); //declare and allocate
    node->total = 7;
    node->numbers = root;
    assert( node->total == 7);
    assert( node->numbers->number == 33);

    //do function
    //printf("Pointer address out of f()::%p\n", newNode);
    bool result  = newNodeSubsetNumbers(
        newNode, node, numToExtract);
    //printf("Pointer address out of f()::%p\n", newNode);
    assert( result);
    assert( newNode != NULL);
    assert( newNode->total == 7);
    assert( newNode->numbers->number == 33);
    //printf("old::%p\n", node->numbers);
    //printf("new::%p\n", newNode->numbers);
    assert( newNode->numbers != node->numbers);

    //test new node with subset list
    int i=0, size=0;
    for( p=newNode->numbers; p != NULL; p=p->back) {
        if( seq[i] == 35) i++;
        assert( p->number == seq[i]); 
        size++;
        i++;
    }
    assert( size == ARRAY_SIZE( seq)-1);
    //go reverse
    for( p=newNode->numbers; p->back != NULL; p=p->back) 
        ;//go to last node
    assert( p->number == 38);
    i = 5;
    for( ; p != NULL; p=p->front) {
        assert( i >= 0);
        if( seq[i] == 35) i--;
        assert( p->number == seq[i]); 
        i--;
    }
    
    //sever root
    freeNode( newNode);
    newNode = nalloc();
    assert( newNode->numbers == NULL);
    assert( root->number == 33);
    newNodeSubsetNumbers( newNode, node, root);
    //test new node with subset list
    i=0, size=0;
    for( p=newNode->numbers; p != NULL; p=p->back) {
        if( seq[i] == 33) i++;
        assert( p->number == seq[i]); 
        size++;
        i++;
    }
    assert( size == ARRAY_SIZE( seq)-1);
    
    //sever last
    freeNode( newNode);
    newNode = nalloc();
    for( p=root; p->back != NULL; p=p->back) 
        ;//go to last node
    numToExtract = p;
    assert( newNode->numbers == NULL);
    assert( numToExtract->number == 38);
    newNodeSubsetNumbers( newNode, node, numToExtract);
    //test new node with subset list
    i=0, size=0;
    for( p=newNode->numbers; p != NULL; p=p->back) {
        if( seq[i] == 38) i++;
        assert( p->number == seq[i]); 
        size++;
        i++;
    }
    assert( size == ARRAY_SIZE( seq)-1);

    //free
    freeNode( node);
    freeNode( newNode);
}
/* Generic function
 */
int f(int n) 
{
    return n + 1;   
}

/* test function pointer
 */
void testFunctionPointers() 
{
    int (*g)(int) = f;
    assert( g(5) == 6);
}

/* Test Problem class
 */
void testProblemClass() 
{
    //check allocation via malloc
    Problem *p = NULL;
    p = (Problem*) malloc(sizeof(Problem));
    assert( p != NULL);
    free(p);

    //check normal declaration
    Problem q;
    q.name = "Hellos";
    assert( strcmp(q.name,"Hellos") == 0);
    
    //check function assignment
    q.f = f; //generic f()
    assert( q.f(47) == 48 );

    //test init for class 
    //assign function to pointerass Problem
    //q.init = __Problem_init; 
    //char *s = "New Class Problem";
    //p = &q;
    //q.init(p, s);
    //assert( strcmp(q.name,s)==0);

    //test constructor
    char *s = "Look for Corners Problem";
    p = ProblemConstructor();
    p->init(p,s);
    assert( strcmp(p->name,s)==0);
    
    //allocate initial state
    State *state = NULL;
    state = p->getInitialState(p);
    int m1=47, m2=48, m3=49;
    int *n1 = &m1, *n2=&m2, *n3=&m3;
    state->p = n1;
    assert( *(int*)(state->p) == 47);
    free(state);

    //array of states
    State **states = NULL;
    states = p->getSuccessors(p,state);
    states[0]->p = n1;
    states[1]->p = n2;
    states[2]->p = n3;
    assert( *(int*)(states[0]->p) == 47);
    assert( *(int*)states[1]->p == 48);
    assert( *(int*)(states[2]->p) == 49);

    //free allocations
    int i;
    for(i=0; i<3; i++) { //3 is hardcoded
        free(states[i]);
    }
    free(states);
    free(p);


    return;   
}

/* try to pass a struct
 * ***Results in invalid read from different stack****
 */
Linkedlist passLinkedList()
{
    Linkedlist list;
    int i = 68, j=76;
    int *d = &i;
    list.content = d;
    Linkedlist list2;
    d = &j;
    list2.content = d;
    list.back = &list2;
    assert( *(int*)list.back->content == 76);
    return list;
}

/* use a struct as a parameter
 * ***Results in invalid read from different stack****
 */
void testLLparam(Linkedlist list) 
{
    assert( *(int*)list.content == 68);
    assert( *(int*)list.back->content == 76);
}

/* test LinkedList
 */
void tLinkedList() 
{
    Linkedlist list;
    int i=3, j=48;
    int *d=&i;
    list.content = d;
    assert( *(int*)list.content == 3);

    Linkedlist list2;
    d = &j;
    list2.content = d;//put in package
    list.back = &list2;//attach
    assert( *(int*)list.back->content == 48);

    //Linkedlist list3 = passLinkedList();
    //assert( *(int*)list3.content == 68);
    //assert( *(int*)list3.back->content == 76);
    //*(int*)list3.back->content=98;
    //assert( *(int*)list3.back->content == 98);

    //testLLparam(passLinkedList());
}

/* test pass qstack
 * RESULTS: changes head and tail pointer
 * values in a local copy but still
 * frees the malloc'd items in stack
 * resulting in undefined state in
 * other copies relying on those
 * gone malloc'd pointers
 */
void testPassedQStack(QStack s) 
{
    struct points { int x; int y; };
    assert( ((struct points*)s.pop(&s))->x == 13);
    assert( ((struct points*)s.pop(&s))->x == 38);
    assert( ((struct points*)s.pop(&s))->x == 5);
}

/* test referenced stack
 */
void testRefStack(QStack *s)
{
    struct points { int x; int y; };
    assert( ((struct points*)s->pop(s))->x == 13);
    assert( ((struct points*)s->pop(s))->x == 38);
    assert( ((struct points*)s->pop(s))->x == 856);
}

/* test QStack operations
 */
void tQstack() 
{
    QStack s = QStackInit();
    struct points { int x; int y; };
    struct points pt={3,6}, pt2={7,1}, pt3={32,9};
    assert( pt.x==3 && pt.y==6 && pt3.x==32);

    s.push(&s,&pt);
    s.push(&s,&pt2);
    s.push(&s,&pt3);

    assert( ((struct points*)s.pop(&s))->x == 32);
    assert( ((struct points*)s.pop(&s))->x == 7);
    assert( ((struct points*)s.pop(&s))->x == 3);
    assert( s.pop(&s) == NULL);

    s.enqueue(&s,&pt);
    s.enqueue(&s,&pt2);
    s.enqueue(&s,&pt3);

    assert( ((struct points*)s.dequeue(&s))->x == 3);
    assert( ((struct points*)s.dequeue(&s))->x == 7);
    assert( ((struct points*)s.dequeue(&s))->x == 32);
    assert( s.dequeue(&s) == NULL );

    struct points *p = malloc(sizeof(struct points)*3);
    p[0].x=5;
    p[0].y=62;
    p[1].x=38;
    p[1].y=1;
    p[2].x=13;
    p[2].y=14;
    //p[3].x=13; //invalid write
    assert( p[1].x == 38);

    s.push(&s,&p[0]);
    s.push(&s,&p[1]);
    s.push(&s,&p[2]);

    //testPassedQStack(s); undefined state

    assert( ((struct points*)s.pop(&s))->x == 13);
    assert( ((struct points*)s.pop(&s))->x == 38);
    assert( ((struct points*)s.pop(&s))->x == 5);

    p[0]=pt; //assign local to malloc'd
    assert( p[0].x == 3);
    s.push(&s,&p[0]);
    assert( ((struct points*)s.pop(&s))->x == 3);
    
    //assign initialization to malloc'd
    p[0] = (struct points) {856,49}; 
    assert( p[0].x == 856);
    s.push(&s,&p[0]);
    assert( ((struct points*)s.pop(&s))->x == 856);

    s.push(&s,&p[0]);
    s.enqueue(&s,&p[1]);
    s.push(&s,&p[2]);

    assert( ((struct points*)s.dequeue(&s))->x == 856);
    assert( s.head != NULL);
    assert( ((struct points*)s.pop(&s))->x == 13);
    assert( ((struct points*)s.dequeue(&s))->x == 38);
    assert( s.dequeue(&s) == NULL );
    assert( s.pop(&s) == NULL );

    //test local to malloc'd
    QStack *stack = (QStack*) malloc(sizeof(QStack));
    *stack = QStackInit();

    stack->push(stack,&p[0]);
    assert( stack->head != NULL);
    stack->enqueue(stack,&p[1]);
    stack->push(stack,&p[2]);

    assert( ((struct points*)stack->dequeue(stack))->x == 856);
    assert( ((struct points*)stack->pop(stack))->x == 13);
    assert( ((struct points*)stack->dequeue(stack))->x == 38);

    stack->push(stack,&p[0]);
    assert( stack->head != NULL);
    stack->enqueue(stack,&p[1]);
    stack->push(stack,&p[2]);
    
    testRefStack(stack);
    assert( stack->dequeue(stack) == NULL );
    assert( stack->pop(stack) == NULL );

    free(stack);
    free(p);//frees entire block (all 3 pointers)
}

/* test node.c
 */
int tnode() 
{
    printf("::hello from tests countdown node\n");
    testnAlloc();
    testNumAlloc();
    testNewNode();
    testNumLinkMaker();
    testNodeLocal();
    testNullAssignment();
    testGetRoot();
    testDelinker();
    testGoalTest();
    testsprintf();
    testGetGoal();
    teststdbool();
    testNewNodeSubsetNum();
    testFunctionPointers();
    testProblemClass();
    tLinkedList();
    tQstack();
    return 0;
}


