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

/*function prototypes*/
node * insert(node* pNode, char* word, int weight);

int main (int argc, char *argv[]){

    Tree.flag = false;

    



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

    else if (/*current char in word is equal to char in pNode*/)
    {
        if (/*next char in word is '\0'*/)
        {
            // set pNode end_of_key_flag to true and assign weight
        }
    }
}