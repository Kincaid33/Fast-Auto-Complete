#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]){

    char *word = "ABCDEFGH";
    int i;
    for(i=0; i<=8; i++) {
        printf("%d  ", (int)(* word+i));
    }
    return 0;
}