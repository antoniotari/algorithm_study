
/* A binary tree node has data, pointer to left child
 and a pointer to right child */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

extern void printPathsRecur(struct node* node, int path[], int pathLen);
extern void printArray(int ints[], int len);
extern void printPaths(struct node* node);
extern struct node* createNodes();
