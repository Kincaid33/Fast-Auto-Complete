#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WORDLENGTH 250

struct node
{
    char character;
    int weight;
    bool end_of_key;
    struct node * left;
    struct node * equal;
    struct node * right;
};

typedef struct node node;

/*function prototypes*/
node * insert(node* pNode, char* word, int weight);
/******************************/
int main (int argc, char *argv[]){
    node *root;
    root = malloc(sizeof(node));
    root->end_of_key = false;
    root->left = NULL;
    root->equal = NULL;
    root->right = NULL;
    root = insert(root, "cat", 3);
    root = insert(root, "cow", 5);
    return 0;
}
// insert each key into a node to form a tree
node * insert(node* pNode, char* word, int weight){
    if (pNode == NULL){
        // create a new node & insert the character
        pNode = malloc(sizeof(node));
        pNode->character=* word;
    }
    // current char in word is smaller than char in pNode
    if ((int) (* word) < (int) pNode->character) {
        // insert the character on the left branch
        pNode->left = insert (pNode->left, word, weight);
    }
    // current char in word is equal to char in pNode
    else if((int) (* word) == (int) pNode->character) {
        // check if the next character is \0 or not
        if (*(word+1) == '\0') {
            pNode->end_of_key = true;
            pNode->weight = weight;
        } else {
            pNode->equal = insert(pNode->equal , word+1, weight);
        }
    }
    // current char in word is greater than char in pNode
    else {
        // insert the character on the right branch
        pNode->right = insert ( pNode->right , word , weight );
    }
    return pNode;
}

