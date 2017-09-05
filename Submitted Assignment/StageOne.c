

/* include the header file */
#include "autocomplete1.h"

/* insert the main function */

int main (int argc, char *argv[]){
    
        //  initilize the ternary search tree
        struct node* root = NULL;
        //  allocate the memory for the prefix to be stored
        char* prefix = malloc(strlen(argv[3]+1) * sizeof(char));
    
        if(strcmp(argv[3], "<") == 0){
            strcpy(prefix, argv[4]);
        } else {
            strcpy(prefix, argv[3]);
        }
        // declare the write file pointer variable
        FILE * fwrite;
        // read and write to file
        fwrite = input_and_output(root, argv[1], argv[2], prefix);
        fclose(fwrite);
        // free the dynamic memory allocated
        free(root);
        return 0;
    }
