#ifndef PROBLEM_H
#define PROBLEM_H

typedef struct state State;
struct state 
{
    void *p;
};

typedef struct problem Problem;
struct problem 
{
    char *name;
    void (*init)(Problem*,char*);
    char *(*getName)(Problem *self);
    State **(*getSuccessors)(Problem *self, State *s);
    State *(*getInitialState)(Problem *self);
    int (*f)(int);
};
Problem *ProblemConstructor();

#endif
