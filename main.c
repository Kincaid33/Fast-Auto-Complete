#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree
{
    char character;
    int weight;
    bool flag;
    struct tree * left;
    struct tree * equal;
    struct tree * right;
};

typedef tree Tree;

int main (int argc, char *argv[]){
    return 0;
}

node * insert(node* pNode, char* word, int weight){
    if (pNode is NULL)
    {
        // create a new pNode, and save a character from word
    }

    if (/*current char in word is smaller than char in pNode*/)
    {
        // insert the character on the left branch
        pNode -> left = insert(pNode -> left, word, weight);
    }

    else if (/*current char in word is equal to char in pData*/)
    {

    }
}