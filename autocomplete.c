#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WORDLENGTH 250

struct node
{
    char character;
    int weight;
    bool end_of_key;
    struct tree * left;
    struct tree * equal;
    struct tree * right;
};

typedef node node;

/*function prototypes*/
node * insert(node* pNode, char* word, int weight);
/******************************/
int main (int argc, char *argv[]){
    char *temp = malloc((WORDLENGTH+1)*sizeof(char));
    char *temp = "Beautiful";
    node pData;
    pData->end_of_key = false;
    root = insert(root, "cat", 3);
    return 0;
}

node * insert(node* pNode, char* word, int weight){
    if (pNode == NULL){
        pNode.Data->word[];
    }
}