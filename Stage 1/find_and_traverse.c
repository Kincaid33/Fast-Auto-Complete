

/* include the header file */
#include "autocomplete1.h"

/* insert the functions */

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
            // fprintf(fp, "prefix_old");
            buffer[strlen(prefix)+1] = '\0';
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