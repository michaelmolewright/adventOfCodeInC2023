#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#define INSTRUCTION_SIZE 263

typedef struct{
    char sourcenode[4];
    char leftnode[4];
    char rightnode[4];
    int rightdestnode;
    int leftdestnode;
} node;

typedef struct{
    node **array;
    int size;
    int used; 
}nodeArray;

void initArray(nodeArray *nodeArray, int initialSize){
    nodeArray->array = malloc(sizeof( node) * initialSize);
    nodeArray->used = 0;
    nodeArray->size = initialSize;
}

void findIndex(nodeArray *nA, node *n){
    for (int i = 0; i <nA->used;i++){
        if( strcmp( n->leftnode, nA->array[i]->sourcenode) == 0){
            n->leftdestnode = i;
        }
        if( strcmp( n->rightnode, nA->array[i]->sourcenode) == 0){
            n->rightdestnode = i;
        }
    }
}

void pushNode(nodeArray *nA, node *n){
    

    if(nA->used == nA->size){
        nA->size *= 2;
        nA->array = realloc(nA->array, sizeof( node) * nA->size);
    }

    node *newNode = malloc(sizeof(node));
    // char *sourceptr = ( char * )malloc(strlen(n->sourcenode) * sizeof(char));
    // char *leftptr = ( char * )malloc(strlen(n->leftnode) * sizeof(char));
    // char *rightptr = ( char * )malloc(strlen(n->rightnode) * sizeof(char));

    nA->array[nA->used] = newNode;
    // newNode->sourcenode = sourceptr;
    // newNode->leftnode = leftptr;
    // newNode->rightnode = rightptr;


    strcpy(newNode->sourcenode, n->sourcenode);
    strcpy(newNode->leftnode, n->leftnode);
    strcpy(newNode->rightnode, n->rightnode);


    nA->used++;
}

int traverse(nodeArray *nA, char *instructions, int s, int f){
    bool finished = false;
    int index = 0;
    int cycle = strlen(instructions);

    int nodeIndex = s;
    node *current = nA->array[s];
    printf("%s\n",current->sourcenode);
    while(!finished){
        char dir = instructions[index%(cycle-1)];
        if (dir == 'L'){
            nodeIndex = current->leftdestnode;
            current = nA->array[nodeIndex];
            //printf("%c, %s, %d, %d\n",dir, current->sourcenode, current->leftdestnode, index);
        }
        if (dir == 'R'){
            nodeIndex = current->rightdestnode;
            current = nA->array[nodeIndex];
            //printf("%c, %s, %d, %d\n",dir, current->sourcenode, current->rightdestnode,index);
        }

        index++;
        if(nodeIndex == f){
            return index;
        }
    } 
    return -1;
}


int main(int argc, char *argv[]){ 

    FILE *fp;

    fp = fopen("./puzzle.txt", "r");
    if(fp == NULL){
        perror("Error");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    getline(&line, &len, fp); 
    char *instructions = strdup(line);
    //printf("%ld, %s\n", strlen(instructions), instructions);

    nodeArray nodes;
    initArray(&nodes, 10);

    while((read = getline(&line, &len, fp)) != -1){
        node new;
        if(strlen(line) > 5 ){
            
            for(int i = 0; i < 3; i++){
                new.sourcenode[i] = line[i];
                new.leftnode[i] = line[i+7];
                new.rightnode[i] = line[i+12];
            }

            new.sourcenode[3] = '\0';
            new.leftnode[3] = '\0';
            new.rightnode[3] = '\0';
                    
            pushNode(&nodes, &new);
        }
    }

    int start, finish;

    for(int i = 0; i < nodes.used;i++){
        findIndex(&nodes, nodes.array[i]);
        if (strcmp (nodes.array[i]->sourcenode, "AAA\0") == 0){
            start = i;
        }
        if (strcmp (nodes.array[i]->sourcenode, "ZZZ\0") == 0){
            finish = i;
        }
        printf("INDEX: %d -- Node: %s, Left: %s (%d), Right: %s (%d)\n", i, nodes.array[i]->sourcenode, nodes.array[i]->leftnode, nodes.array[i]->leftdestnode, nodes.array[i]->rightnode, nodes.array[i]->rightdestnode);

    }    
        //printf("INDEX: %d -- Node: %s, Left: %s (%d), Right: %s (%d)\n", i, nodes.array[i]->sourcenode, nodes.array[i]->leftnode, nodes.array[i]->leftdestnode, nodes.array[i]->rightnode, nodes.array[i]->rightdestnode);

    // }
    printf("%d,%d\n", start, finish);
    int answer = traverse(&nodes, instructions, start, finish);
    printf("Final Answer = %d\n", answer);


    fclose(fp);

}