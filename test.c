#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WORDLENGTH 250

struct node
{
    char character;
    int weight;
    bool end_of_key: 1;
    struct node * left, * equal, * right;
};

/*function prototypes*/
struct node* create_node(char key);
struct node* insert(struct node* pNode, char* word, int weight);
void find_and_traverse(struct node* pNode, char* prefix);
void traverse(struct node * pNode, char* buffer, int depth, char* prefix_old);
// void traversal_tree(struct node* pNode);

/******************************/

int main (int argc, char *argv[]){
    
    struct node* root = NULL;

    /******************TEST CASES**********************/
    // root = insert(root, "cat", 5);
    // root = insert(root, "dog", 7);
    // root = insert(root, "camel", 5);
    // root = insert(root, "ant", 5);
    // root = insert(root, "caterpillar",7);


    // printf("The following words are inserted in the tree:\n");
    // traversal_tree(root);
    // printf("\n");

    // printf("The prefix returns the following words:\n");
    // find_and_traverse(root, "cat");
    free(root);
    return 0;
}
// create a new ternary search tree node
struct node* create_node(char key){
    struct node* newNode = (struct node *) malloc(sizeof(struct node));
    newNode->character = key;
    newNode->weight = 0;
    newNode->end_of_key = false;
    newNode->left = NULL;
    newNode->equal = NULL;
    newNode->right = NULL;
    return newNode;
}
// insert each key into a node to form a tree
struct node* insert(struct node* pNode, char* word, int weight){
    if (pNode == NULL){
        // create a new node & insert the character
        pNode = create_node(* word);
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
        pNode->right = insert (pNode->right , word , weight);
    }
    return pNode;
}

void find_and_traverse(struct node * pNode, char* prefix){
    char buffer[WORDLENGTH];
    char prefix_old[WORDLENGTH+1];
    strcpy(prefix_old, prefix);

    while(*(prefix) != '\0' && pNode != NULL) {
        // go to left branch
        if((* prefix) < pNode->character) {
            pNode = pNode->left;
            continue;
        }
        // go to equal branch
        // go to right branch
        if((* prefix) > pNode->character) {
            pNode = pNode->right;
            continue;
        }
        if((* prefix) == pNode->character) {
            // buffer[strlen(prefix)+1] = '\0';
            prefix++;
            pNode = pNode->equal;
            continue;
        }   
    }
    if(pNode != NULL) {

        // include the prefix itself as a candidate if prefix is a key

        if(pNode->end_of_key == true) {
            buffer[strlen(prefix)+1] = * prefix;
            printf("%s\n", (buffer));
        }
        // print all the keys that contain the prefix
        traverse(pNode, buffer, strlen(prefix), prefix_old);
    }
    else {
        printf("NOT FOUND\n");
    }
}

// just traverse the tree for all the inserted nodes
// void traversal_tree(struct node* pNode){
//     char buffer[WORDLENGTH];
//     traverse(pNode, buffer, 0);
// }

// tree traversal from a given node
void traverse(struct node* pNode, char* buffer, int depth, char* prefix_old){
    if(pNode == NULL) {
        return;
    }
    
    // go to the left most branch first
    traverse(pNode->left, buffer, depth, prefix_old);

    // if no more left branches, then save the character
    buffer[depth] = pNode->character;
    if(pNode->end_of_key == true) {
        buffer[depth + 1] = '\0';
        printf("%s", buffer);
        // printf("%s%s\n", prefix_old, buffer);
    }
    // go to the equal branch
    // advancing to the next character of the key
    traverse(pNode->equal, buffer, depth+1, prefix_old);

    // Finally go to the branches that contain 
    // characters greater than the current one in the buffer
    traverse(pNode->right, buffer, depth, prefix_old);
}