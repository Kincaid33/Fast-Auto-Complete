

/* include the header file */
#include "autocomplete1.h"


// read from a given data file and insert into the nodes
FILE * input_and_output(struct node* pNode, char* datafile, char* outputfile , char* prefix) {
    
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
        comparisons = find_and_traverse(pNode, prefix, fp);
        printf("Prefix:  %s found with %d char comparisons\n", prefix, comparisons);
    
        fclose(fr);
        return fp;
    }
    