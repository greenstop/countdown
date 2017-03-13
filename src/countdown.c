#include <countdown.h>
#include <node.h>

#define DEBUG true
#define DB if( DEBUG)
#define MAX_ITERATIONS 2000000
char actions[] = {'+','-','*','/'};
int actionsSize = ARRAY_SIZE( actions);
int iteration = 0;
int solutions = 0;

/* do recursive depth graph search
 */
bool search( struct node *node, int depth) 
{
    //Prune //!Prunes valid solutions
    //if( node->total > getGoal()) return false;

    struct numNode *p = NULL, *pD = NULL;

    //DEBUG
    int d=0, j=0;
    double prevTotal = node->total;
    DB for(d=0; d < depth; d++) printf("\t"); 
    DB printf("[%d =%.0f:", depth, node->total);
    for( pD=node->numbers; pD != NULL; pD=pD->back)
        DB printf("%.0f,", pD->number);
    DB printf("]\n");

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

            //test goal
            bool result = goalTest( node, p, actions[i]);
            
            //DEBUG
            DB if( actions[i] == '-')
                assert( node->total == (prevTotal - p->number));
            DB assert( actionsSize == 4);
            DB assert( i<4);
            DB for(d=0; d < depth; d++) printf("\t"); 
            DB printf("(%d:%d:%d %.0f%c=%.1f)\n",
                depth, j, i,
                p->number, actions[i], node->total);

            if( result) {
                //char string[100];
                //sprintf( string,
                //    "Found Solution in %d", iteration);
                //exitError( 200, string);
                solutions++;
            }
            else {
                struct node *newNode = nalloc();
                
                //DEBUG
                DB assert( newNode->numbers == NULL);

                result = false;
                if( newNodeSubsetNumbers( newNode, node, p)) {
                    //DEBUG
                    DB assert( newNode != NULL);
                    DB assert( newNode->total == node->total);
                    DB assert( newNode->numbers != NULL);
                    //DB for(d=0; d < depth+1; d++) printf("\t"); 
                    //DB printf("{%d:%d %.0f, ", depth, i, node->total);
                    //DB for( pD=newNode->numbers; pD != NULL; pD=pD->back)
                    //    DB printf("%.0f:", pD->number);
                    //DB printf("}\n");

                    result = search( newNode, depth+1);
                } else result = false; 
                if( result == false) freeNode( newNode);
            }
            node->total = prevTotal;
        }
        j++;
    }
    return false;
}

int main () 
{
    //727; 50, 100, 9, 1, 9, 3
    //(9-1)50+(100+9)3
    //TODO account for multiple uses of 50 and 3
    printf("hello from countdown\n");

    assert( actionsSize == 4);

    //setup
    //setGoal( 801);
    //int seq[] = {75, 25, 4 ,9, 10, 5};
    setGoal( 226);
    int seq[] = {3,7,9,1,5,100};
    //setGoal( 363);
    //int seq[] = {100, 75, 10, 6, 7, 10};
    //setGoal( 727);
    //int seq[] = {50, 100, 9, 1, 9, 3};
    //setGoal( 350);
    //int seq[] = {6 , 75, 100};
    struct numNode *root = NULL;
    root = numLinkFromArray( seq, ARRAY_SIZE( seq));
    //initial node
    struct node *node = nalloc();
    node->numbers = root;

    //start search
    printf("Starting Search ...\n");
    search( node, 0);
    printf("Search Stopped. %d solutions... in %d\n", solutions, iteration);
    freeNode( node);
}



