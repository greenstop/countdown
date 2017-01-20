#include <countdown.h>
#include <node.h>

#define DEBUG false
#define DB if( DEBUG)
#define MAX_ITERATIONS 1000000
char actions[] = {'+','-','*','/'};
int actionsSize = ARRAY_SIZE( actions);
int iteration = 0;

/* do recursive depth graph search
 */
bool search( struct node *node, int depth) 
{
    //Prune
    if( node->total > getGoal()) return false;

    struct numNode *p = NULL, *pD = NULL;

    //DEBUG
    int d=0;
    DB printf("[%d:%.0f]", depth, node->total);
    for( pD=node->numbers; pD != NULL; pD=pD->back)
        DB printf("%.0f:", pD->number);
    DB printf("\n");

    for( p=node->numbers; p != NULL; p=p->back) {
        int i;
        for( i=0; i < actionsSize; i++) {
            //restrict
            iteration++;
            if( iteration > MAX_ITERATIONS) exitError( 509,"");

            //Prune
            if( node->total == 0 &&
                (actions[i] == '*' || actions[i] == '/'))
                continue;

            //searching
            bool result = goalTest( node, p, actions[i]);
            
            //DEBUG
            DB assert( actionsSize == 4);
            DB assert( i<4);
            DB for(d=0; d < depth; d++) printf("\t"); 
            DB printf("  (%.0f%c=%.1f:%d) \n",
                p->number, actions[i], node->total, i);

            if( result) {
                char string[100];
                sprintf( string,
                    "Found Solution in %d", iteration);
                exitError( 200, string);
            }
            else {
                struct node *newNode = nalloc();
                
                //DEBUG
                DB assert( newNode->numbers == NULL);

                result = false;
                if( newNodeSubsetNumbers( newNode, node, p)) {
                    //DEBUG
                    DB assert( newNode != NULL);
                    DB assert( newNode->numbers != NULL);
                    DB for(d=0; d < depth+1; d++) printf("\t"); 
                    DB printf("{%d:%.0f, ", depth, node->total);
                    DB for( pD=newNode->numbers; pD != NULL; pD=pD->back)
                        DB printf("%.0f:", pD->number);
                    DB printf("}");

                    result = search( newNode, depth+1);
                } else result = false; 
                if( result == false) freeNode( newNode);
            }
        }
    }
    return false;
}

int main () 
{
    //727; 50, 100, 9, 1, 9, 3
    //(9-1)50+(100+9)3
    //TODO account for multiple uses of 50 and 3
    printf("hello from countdown::\n");

    assert( actionsSize == 4);

    //setup
    //setGoal( 801);
    setGoal( 727);
    //number linked list
    //int seq[] = {75, 25, 4 ,9, 10, 5};
    int seq[] = {50, 100, 9, 1, 9, 3};
    //int seq[] = {4 , 10};
    struct numNode *root = NULL;
    root = numLinkFromArray( seq, ARRAY_SIZE( seq));
    //initial node
    struct node *node = nalloc();
    node->numbers = root;

    //start search
    printf("Starting Search ...\n");
    bool result = search( node, 0);
    printf("Search Stopped. Success? %x... in %d\n", result, iteration);
    freeNode( node);
}



