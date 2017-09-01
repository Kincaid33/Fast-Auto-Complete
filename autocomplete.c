#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
void find_and_traverse(node* pNode, char* prefix);
void traverse(node* pNode, char* buffer, int depth);
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
    root = insert(root, "dog", 2);
    find_and_traverse(root, "ca");
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
    if ((* word) < pNode->character) {
        // insert the character on the left branch
        pNode->left = insert (pNode->left, word, weight);
    }
    // current char in word is equal to char in pNode
    else if((* word) == pNode->character) {
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
        pNode->right = insert ( pNode->right , word , weight);
    }
    return pNode;
}


void find_and_traverse(node* pNode, char* prefix){
    char * buffer = malloc((WORDLENGTH+1)*(sizeof(char)));

    while(*prefix != '\0' && pNode != NULL) {
       
        // go to left branch
        if((* prefix) < pNode->character) {
            find_and_traverse(pNode->left, prefix);
            continue;
        }
        // go to right branch
        if((* prefix) > pNode->character) {
            find_and_traverse(pNode->right, prefix);
            continue;
        }
        // go to equal branch
        if((* prefix) == pNode->character) {
            find_and_traverse(pNode->equal, prefix+1);
            continue;
        }
    }

    if(pNode != NULL) {
        if(pNode->end_of_key == true) {
            buffer[strlen(prefix)+1] = '\0';
            printf("%s\n", buffer);
        }

        traverse(pNode, buffer, strlen(prefix));
    }
}

// tree traversal from a given node
void traverse(node* pNode, char* buffer, int depth){
    if(pNode == NULL) return;

    // go to the left most branch first
    traverse(pNode->left, buffer, depth);

    // if no more left branches, then save the character
    buffer[depth] = pNode->character;
    if(pNode->end_of_key == true) {
        buffer[depth + 1] = '\0';
        printf("%s\n", buffer);
    }
    // go to the equal branch
    // advancing to the next character of the key
    traverse(pNode->equal, buffer, depth+1);

    // Finally go to the branches that contain 
    // characters greater than the current one in the buffer
    traverse(pNode->right, buffer, depth);
}