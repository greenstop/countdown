//#include <countdown.h>
#include <problem.h>
#include <stdlib.h>

/* initialization method for Problem class
 */
void __Problem_init(Problem *this, char *name) 
{
    this->name = name;
    //printf("hello from Problem %s\n", this->name);
}

/* name method for Problem class
 */
char *__Problem_getName(Problem *this) 
{
    return this->name;
}

/* get successor states method for Problem class
 */
State **__Problem_getSuccessors(Problem *this, State *s) 
{
    //evaluate s
    int NSuccessors = 3;//some n numbe of states
    //allocate for 3 pointers to states
    State **states = (State**) malloc(NSuccessors*sizeof(State*));
    int i;
    for(i=0; i<NSuccessors; i++) {
        states[i] = (State*) malloc(sizeof(State));
    }
    return states; //a pointer to a state pointer
}

/* get initial state method for Problem class
 */
State *__Problem_getInitialState(Problem *this) 
{
    //initialize
    State *s = (State*) malloc(sizeof(State));
    return s;
}

/* Allocate new Problem object
 */
Problem *ProblemConstructor() 
{
    Problem *p = NULL;
    p = (Problem*) malloc(sizeof(Problem));

    //assign methods
    p->init = __Problem_init;
    p->getName = __Problem_getName;
    p->getSuccessors = __Problem_getSuccessors;
    p->getInitialState = __Problem_getInitialState;

    return p;
}
