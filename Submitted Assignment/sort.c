/* include the header file */

#include "autocomplete2.h"

// create a new ternary search tree node and 

// function to swap the weights
void int_swap(int* val1, int* val2){
    int temp = * val1;
    * val1 = * val2;
    * val2 = temp;
}
// function to swap the strings 
void char_swap(char** word1, char** word2){
    
    char* temp = *word1;
    *word1 = *word2;
    *word2 = temp;
}

void selection_sort(Data* data_arr){

    // declare the variables required
    int i, j, minimum, compare = 0;

    // loop through all the structs
    for(i = 0; i < data_arr[0].count - 1; i++) {

        // set current index as the minimum
        minimum = i;

        // search for the smallest weight
        for(j = i+1; j < data_arr[0].count; j++) {
            if(data_arr[j].weight < data_arr[minimum].weight) {
                minimum = j;
            }

            // count the number of swaps hence the number of comparisons
            compare++;

            // swap the struct elements
            int_swap(&data_arr[minimum].weight, &data_arr[i].weight);
            char_swap(&data_arr[minimum].item, &data_arr[i].item);
        }
    }
    // store the comparisons in the struct
    data_arr[1].count = compare;
}
