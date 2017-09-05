
/* include all the library files */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* insert all the declarations */

#define WORDLENGTH 250
#define RMODE "r"
#define WMODE "w"
#define MAXSEARCHKEY 100000

//  struct to store the ternary search tree
struct node
{
	char character;
	int weight;
	bool end_of_key: 1;
	struct node * left, * equal, * right;
};
//  struct to store information for selection sort
struct data
{
	int weight;
    char *item;
    int count;
};
typedef struct data Data;
/*insert all the function prototypes */

struct node* create_node(char key);
FILE * input_and_output(struct node* pNode, char* datafile, char* outputfile , char* prefix,  Data* data_arr);
struct node* insert(struct node* pNode, char* word, int weight);
int find_and_traverse(struct node * pNode, char* prefix, FILE* fp, Data* data_arr);
void traverse(struct node* pNode, char* buffer, int depth, char* prefix_old, FILE* fp, Data* data_arr);
void int_swap(int* val1, int* val2);
void char_swap(char** word1, char** word2);
void selection_sort(Data* data_arr);
