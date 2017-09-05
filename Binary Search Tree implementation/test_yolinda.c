
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

struct binary_node
{
	int weight;
	char *item;
	struct binary_node * left, * right;
};

struct info
{
	char*item;
	int weight;
};

/*insert all the function prototypes */

struct node* create_node(char key);
FILE * input_and_output(struct node* pNode, struct binary_node * bNode, char* datafile, char* outputfile , char* prefix);
struct node* insert(struct node* pNode, char* word, int weight);
int find_and_traverse(struct node * pNode, struct binary_node * bNode, char* prefix, FILE* fp);
void traverse(struct node* pNode, struct binary_node * bNode, char* buffer, int depth, char* prefix_old, FILE* fp);
void insert_binary(struct binary_node ** bNode, char* prefix_comb, int weight);
void traverse_binary_tree(struct binary_node * bNode, FILE* fp);

/* insert the main function */

int main (int argc, char *argv[]){

		// initilize the ternary search tree
		struct node* root = NULL;
		// initialize the binary search tree
		struct binary_node *binary_root = NULL;
		//  allocate the memory for the prefix to be stored
		char* prefix = malloc(strlen(argv[3]+1) * sizeof(char));
		strcpy(prefix, argv[3]);
		// declare the write file pointer variable
		FILE * fwrite;
		// read and write to file
		fwrite = input_and_output(root, binary_root, argv[1], argv[2], prefix);
		// free the dynamic memory allocated
		// insert_binary(&binary_root, "cat", 9);
		// insert_binary(&binary_root, "dog", 4);
		// insert_binary(&binary_root, "ant", 15);
		// insert_binary(&binary_root, "ball", 6);
		// insert_binary(&binary_root, "yolk", 12);
		// insert_binary(&binary_root, "cow", 17);
		// insert_binary(&binary_root, "joke", 2);

		traverse_binary_tree(binary_root, fwrite);
		fclose(fwrite);
		free(binary_root);
		free(root);

		return 0;
	}

/* insert the functions */

// read from a given data file and insert into the nodes
FILE * input_and_output(struct node* pNode, struct binary_node* bNode, char* datafile, char* outputfile , char* prefix) {
	
	// declare file pointers
	FILE *fr, *fp;
	char ch = 'a';
	int comparisons;

	// declare the variables to read prefix and weight
	int inputWeight = 0;
	char* word = (char *) malloc((WORDLENGTH+1) * sizeof(char));

	// open the data file and the write files
	fr = fopen(datafile, RMODE);
	fp = fopen(outputfile, WMODE);

	// exit if not possible to read from files
	if((fr == NULL) || (fp == NULL)) {
		printf("Failed to open data file\n");
		exit(EXIT_FAILURE);
	}
	// scan for the data from the data file
	while(fscanf(fr, "%d; %[^\n]s", &inputWeight, word) && (ch = fgetc(fr) != EOF )) {
		pNode = insert(pNode, word, inputWeight);
	}

	// print to the output file
	fprintf(fp, "\n");
	fprintf(fp, "Prefix:  %s\n", prefix);
	comparisons = find_and_traverse(pNode, bNode, prefix, fp);
	printf("Prefix:  %s found with %d char comparisons\n", prefix, comparisons);
	traverse_binary_tree(bNode, fp);
	fclose(fr);
	return fp;
}
	
/* insert the functions */

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

/* insert the functions */

// look for a particular key word
int find_and_traverse(struct node * pNode, struct binary_node * bNode, char* prefix, FILE* fp){
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
		// buffer[strlen(prefix)] = pNode->character;

		if(pNode->end_of_key == true) {
			buffer[strlen(prefix)+1] = '\0';
			fprintf(fp, "%s", (buffer));
		}
		// print all the keys that contain the prefix
		traverse(pNode, bNode, buffer, strlen(prefix), prefix_old, fp);
	}
	else {
		fprintf(fp, "NOTFOUND\n");
	}
	return comparisons;
}


// tree traversal from a given node
void traverse(struct node* pNode, struct binary_node * bNode, char* buffer, int depth, char* prefix_old, FILE* fp) {
	if(pNode == NULL) {
		return;
	}
	// go to the left most branch first
	traverse(pNode->left, bNode, buffer, depth, prefix_old, fp);
	// if no more left branches, then save the character
	buffer[depth] = pNode->character;
	char * prefix_comb = (char*)malloc((strlen(prefix_old)+strlen(buffer))*sizeof(char));
	if(pNode->end_of_key == true) {
		buffer[depth + 1] = '\0';
		strcpy(prefix_comb, prefix_old);
		strcat(prefix_comb, buffer);
		// fprintf(fp, "%s --> weight:  %d\n", prefix_comb, pNode->weight);
		// insert_binary(&bNode, prefix_old, 5);
	}
	// go to the equal branch
	// advancing to the next character of the key
	traverse(pNode->equal, bNode, buffer, depth+1, prefix_old, fp);
	// Finally go to the branches that contain
	// characters greater than the current one in the buffer
	traverse(pNode->right, bNode, buffer, depth, prefix_old, fp);
}

// create a new ternary search tree node and

void insert_binary(struct binary_node ** bNode, char* prefix_comb , int weight) {
	
	if(!(*bNode)) {
		*bNode = (struct binary_node *) malloc(sizeof(struct binary_node));
		(*bNode)->item = strdup(prefix_comb);
		(*bNode)->weight = weight;
		(*bNode)->left = (*bNode)->right = NULL;
	}
	if(weight < (*bNode)->weight) {
		insert_binary(&(*bNode)->left, prefix_comb, weight);
	}
	else if(weight > (*bNode)->weight) {
		insert_binary(&(*bNode)->right, prefix_comb, weight);
	}
}

void traverse_binary_tree(struct binary_node * bNode, FILE* fp) {
	if (bNode)
	{
		traverse_binary_tree(bNode->right, fp);
		fprintf(fp, "KEY:  %s --> weight:  %d\n", (bNode->item), bNode->weight);
		traverse_binary_tree(bNode->left, fp);
	}
}