#ifndef TREENODE_H
#define TREENODE_H

#include <node.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_PATH 107
#define MAX_N 10

#define ARRAY_SIZE( array) sizeof(array)/sizeof(array[0])

struct numNode
{
    double number;
    struct numNode *front;
    struct numNode *back;
};

struct node
{
    double total;
    //char *path;
    struct numNode *numbers;
};

struct node *nalloc();
struct numNode *numNodealloc();
bool goalTest(
    struct node *p,
    struct numNode *n,
    char action);
void setGoal(
    int goalee); 
struct numNode * numNodeDelinker(
    struct numNode *p);
struct numNode * numLinkFromArray(
    int *nSeq,
    int nSize);
bool numNLinkDestroyer(
    struct numNode *root);
struct numNode * rootOfNode(
    struct numNode *node);
int getGoal(); 
void freeNode(
    struct node *node);
bool newNodeSubsetNumbers(
    struct node *newNode,
    struct node *node,
    struct numNode *numToBeExtracted);
void exitError(int action, char *s);

#endif
