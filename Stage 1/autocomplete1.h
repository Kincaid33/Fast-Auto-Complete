
/* include all the library files */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* insert all the declarations */

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

/*insert all the function prototypes */

struct node* create_node(char key);
FILE * input_and_output(struct node* pNode, char* datafile, char* outputfile , char* prefix);
struct node* insert(struct node* pNode, char* word, int weight);
int find_and_traverse(struct node* pNode, char* prefix, FILE* fp);
void traverse(struct node * pNode, char* buffer, int depth, char* prefix_old, FILE* fp);

