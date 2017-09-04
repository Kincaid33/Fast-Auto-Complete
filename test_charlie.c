#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WORDLENGTH 250
#define RMODE "r"
#define WMODE "w"

struct node
{
    char character;
    int weight;
    bool end_of_key: 1;
    struct node * left, * equal, * right;
};

/*function prototypes*/
struct node* create_node(char key);
FILE * input_and_output(struct node* pNode, char* datafile, char* outputfile , char* prefix);
struct node* insert(struct node* pNode, char* word, int weight);
int find_and_traverse(struct node* pNode, char* prefix, FILE* fp);
void traverse(struct node * pNode, char* buffer, int depth, char* prefix_old, FILE* fp);
/******************************/

int main (int argc, char *argv[]){

    //  initilize the ternary search tree
    struct node* root = NULL;
    //  allocate the memory for the prefix to be stored
    char* prefix = malloc(strlen(argv[3]+1) * sizeof(char));
    strcpy(prefix, argv[3]);
    //  initialize the file to be read
    FILE * fwrite;
    // read and write to file
    fwrite = input_and_output(root, argv[1], argv[2], prefix);
    fclose(fwrite);
    // free the dynamic memory allocated
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

// read from a given data file and insert into the nodes
FILE * input_and_output(struct node* pNode, char* datafile, char* outputfile , char* prefix) {
    FILE *fr, *fp;
    char ch = 'a';
    int comparisons;
    
    int inputWeight = 0;
    char* word = (char *) malloc((WORDLENGTH+1) * sizeof(char));
    
    fr = fopen(datafile, RMODE);
    fp = fopen(outputfile, WMODE);

    if((fr == NULL) || (fp == NULL)) {
        printf("Failed to open data file\n");
        exit(EXIT_FAILURE);
    }

    while(fscanf(fr, "%d; %[^\n]s", &inputWeight, word) && (ch = fgetc(fr) != EOF )) {
        pNode = insert(pNode, word, inputWeight);
    }
    fprintf(fp, "Prefix:  %s\n", prefix);
    comparisons = find_and_traverse(pNode, prefix, fp);
    printf("Prefix:  %s found with %d char comparisons\n", prefix, comparisons);

    fclose(fr);
    return fp;
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

// look for a particular key word
int find_and_traverse(struct node * pNode, char* prefix, FILE* fp){
    char * buffer = malloc((WORDLENGTH+1)*sizeof(char));
    int comparisons = 0;
    char prefix_old[WORDLENGTH+1];
    strcpy(prefix_old, prefix);
    while(*(prefix) != '\0' && pNode != NULL) {
        // go to left branch
        comparisons++;
        if((* prefix) < pNode->character) {
            pNode = pNode->left;
            continue;
        }
        // go to right branch
        if((* prefix) > pNode->character) {
            pNode = pNode->right;
            continue;
        }
        // go to equal branch
        if((* prefix) == pNode->character) {
            prefix++;
            pNode = pNode->equal;
            continue;
        } 
    }
    if(pNode != NULL) {

        // include the prefix itself as a candidate if prefix is a key
        if(pNode->end_of_key == true) {
            buffer[strlen(prefix)+1] = * prefix;
            fprintf(fp, "%s", (buffer));
        }
        // print all the keys that contain the prefix
        traverse(pNode, buffer, strlen(prefix), prefix_old, fp);
    }
    else {
        fprintf(fp, "NOTFOUND\n");
    }
    return comparisons;
}

// tree traversal from a given node
void traverse(struct node* pNode, char* buffer, int depth, char* prefix_old, FILE* fp) {
    if(pNode == NULL) {
        return;
    }
    
    // go to the left most branch first
    traverse(pNode->left, buffer, depth, prefix_old, fp);

    // if no more left branches, then save the character
    buffer[depth] = pNode->character;
    if(pNode->end_of_key == true) {
        buffer[depth + 1] = '\0';
        // printf("%s", buffer);
        fprintf(fp, "%s%s --> weight:  %d\n", prefix_old, buffer, pNode->weight);
    }
    // go to the equal branch
    // advancing to the next character of the key
    traverse(pNode->equal, buffer, depth+1, prefix_old, fp);

    // Finally go to the branches that contain 
    // characters greater than the current one in the buffer
    traverse(pNode->right, buffer, depth, prefix_old, fp);
}