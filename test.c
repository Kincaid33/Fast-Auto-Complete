#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WORDLENGTH 250


int main(int argc, char *argv[]){
    char * prefix = "Melb";
    char * buffer = malloc((WORDLENGTH+1)*(sizeof(char)));
    buffer[strlen(prefix)+1] = '\0';
    printf("%c", * prefix);
    printf("apple%s|", buffer);
    return 0;
}
