
/* include the header file */
#include "autocomplete2.h"

/* insert the functions */

// look for a particular key word
int find_and_traverse(struct node * pNode, char* prefix, FILE* fp,  Data* data_arr){
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
			buffer[strlen(prefix)+1] = '\0';
			fprintf(fp, "%s", (buffer));
		}
        // print all the keys that contain the prefix
        data_arr[0].count = 0;
        traverse(pNode, buffer, strlen(prefix), prefix_old, fp, data_arr);
        selection_sort(data_arr);
	}
	else {
		fprintf(fp, "NOTFOUND\n");
	}
	return comparisons;
}

// tree traversal from a given node
void traverse(struct node* pNode, char* buffer, int depth, char* prefix_old, FILE* fp,  Data* data_arr) {
	if(pNode == NULL) {
		return;
	}
	// go to the left most branch first
	traverse(pNode->left, buffer, depth, prefix_old, fp, data_arr);
	// if no more left branches, then save the character
	buffer[depth] = pNode->character;
    char * prefix_comb = (char*)malloc((strlen(prefix_old)+strlen(buffer))*sizeof(char));
	if(pNode->end_of_key == true) {
		buffer[depth + 1] = '\0';
		strcpy(prefix_comb, prefix_old);
        strcat(prefix_comb, buffer);
        data_arr[data_arr[0].count].item = prefix_comb;
        data_arr[data_arr[0].count].weight = pNode->weight;
        data_arr[0].count = data_arr[0].count + 1;
	}
	// go to the equal branch
    // advancing to the next character of the key
    traverse(pNode->equal, buffer, depth+1, prefix_old, fp, data_arr);
	// Finally go to the branches that contain
	// characters greater than the current one in the buffer
    traverse(pNode->right, buffer, depth, prefix_old, fp, data_arr); 
}
