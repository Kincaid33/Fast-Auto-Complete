

/* include the header file */
#include "autocomplete1.h"

/* insert all the functions */

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
        pNode->right = insert(pNode->right , word , weight);
    }
    return pNode;
}

