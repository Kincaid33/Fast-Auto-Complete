#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int print(char * word);


int main(int argc, char *argv[]){

    printf("%d", print("cat"));
    return 0;
}

int print(char * word){
    int temp = (int)(* (word+1));
    return temp;
}