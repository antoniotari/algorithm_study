//
//  main.c
//  algorithm study c
//
//  Created by Antonio Tari on 6/16/15.
//  Copyright (c) 2015 ___ANTONIO_TARI___. All rights reserved.
//

#include <stdio.h>
//#include "PrintPathToLeafs.c"

static const float VALUE = 4.82345435647456;

/* A binary tree node has data, pointer to left child
 and a pointer to right child */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

/* Prototypes for funtions needed in printPaths() */
void printPathsRecur(struct node* node, int path[], int pathLen);
void printArray(int ints[], int len);
struct node* createNodes();

/*Given a binary tree, print out all of its root-to-leaf
 paths, one per line. Uses a recursive helper to do the work.*/
void printPaths(struct node* node)
{
    int path[1000];
    printPathsRecur(node, path, 0);
}

/* Recursive helper function -- given a node, and an array containing
 the path from the root node up to but not including this node,
 print out all the root-leaf paths.*/
void printPathsRecur(struct node* node, int path[], int pathLen)
{
    if (node==NULL)
        return;
    
    /* append this node to the path array */
    path[pathLen] = node->data;
    pathLen++;
    
    /* it's a leaf, so print the path that led to here  */
    if (node->left==NULL && node->right==NULL)
    {
        printArray(path, pathLen);
    }
    else
    {
        /* otherwise try both subtrees */
        printPathsRecur(node->left, path, pathLen);
        printPathsRecur(node->right, path, pathLen);
    }
}


/* UTILITY FUNCTIONS */
/* Utility that prints out an array on a line. */
void printArray(int ints[], int len)
{
    int i;
    for (i=0; i<len; i++)
    {
        printf("%d ", ints[i]);
    }
    printf("\n");
}

/* utility that allocates a new node with the
 given data and NULL left and right pointers. */
struct node* newnode(int data)
{
    struct node* node = (struct node*)
    malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    
    return(node);
}

struct node* createNodes(){
    /* Constructed binary tree is
        10
      /    \
     8      2
    / \    /
   3   5  2
     */
    struct node *root = newnode(10);
    root->left        = newnode(8);
    root->right       = newnode(2);
    root->left->left  = newnode(3);
    root->left->right = newnode(5);
    root->right->left = newnode(2);
    return root;
}


/*
 * Calculate the square root of a double
 * Quake 3 solution
*/
float fast_sqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    
    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                     // floating point bit level hacking [sic]
    i  = 0x5f3759df - ( i >> 1 );             // Newton's approximation
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
    y  = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration
    y  = y * ( threehalfs - ( x2 * y * y ) ); // 3rd iteration
    
    return 1/y;
}

/* Assumes that float is in the IEEE 754 single precision floating point format
 * and that int is 32 bits. */
float sqrt_approx(float z){
    int val_int = *(int*)&z; /* Same bits, but as an int */
    /*
     * To justify the following code, prove that
     *
     * ((((val_int / 2^m) - b) / 2) + b) * 2^m = ((val_int - 2^m) / 2) + ((b + 1) / 2) * 2^m)
     *
     * where
     *
     * b = exponent bias
     * m = number of mantissa bits
     *
     * .
     */
    
    val_int -= 1 << 23; /* Subtract 2^m. */
    val_int >>= 1; /* Divide by 2. */
    val_int += 1 << 29; /* Add ((b + 1) / 2) * 2^m. */
    //val_int = (1 << 29) + (val_int >> 1) - (1 << 22) + a;
    return *(float*)&val_int; /* Interpret again as float */
}



int main(int argc, const char * argv[]) {
    float squa = fast_sqrt(VALUE);
    printf("Hello, World!\n%.6f\n%.6f\n", squa,sqrt_approx(VALUE));
    
    printPaths(createNodes());
    
    return 0;
}

