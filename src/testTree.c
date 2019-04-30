/**
 * @file testTree.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing unit testing of AVL tree implementation
 */
#include "test.h"
#include "balancedTreeAPI.h"

int compare(void *first,void *second);
void destroy(void *toBeDeleted);
void *copy(void *toBeCopy);
void printNodeFP(void *data);


int main(int argc, char **argv)
{
    int testNumber = 0;
    int testsPassed = 0;
    Tree *newTree;
    TreeNode *newTreeNode;
    int *num, *num20, *num6, *num8, *num10, *num25, *num9, *num11, temp;

    printf("*******************Start Testing Section*******************\n\n");

    newTree = createBalancedBinTree(compare, destroy, *copy);
    testNumber++;
    printTestInfo(testNumber, "Testing to creat a new balanced bin tree");
    printf("Expect: Not NULL\n");
    printf("Received: %p\n", (void *)newTree);
    testsPassed += printPassFail(newTree != NULL);

    newTreeNode = createBalancedBinNode(NULL);
    testNumber++;
    printTestInfo(testNumber, "Testing to creat a new balanced bin node (NULL)");
    printf("Expect: Not NULL\n");
    printf("Received: %p\n", (void *)newTreeNode);
    testsPassed += printPassFail(newTreeNode != NULL);
    free(newTreeNode);

    num20 = malloc(sizeof(int));
    *num20 = 20;
    treeInsertNode(newTree, num20);
    testNumber++;
    printTestInfo(testNumber, "Testing to insert a number to the tree");
    printf("Expect: %d\n",*num20);
    printf("Received: %d\n", *((int*)(newTree->root->data)));
    testsPassed += printPassFail(((int *)(newTree->root->data)) == num20);

    num10 = malloc(sizeof(int));
    *num10 = 10;
    treeInsertNode(newTree, num10);
    testNumber++;
    printTestInfo(testNumber, "Testing to insert a number to the tree");
    printf("Expect: %d\n",*num10);
    printf("Received: %d\n", *((int*)(newTree->root->left->data)));
    testsPassed += printPassFail(((int *)(newTree->root->left->data)) == num10);

    num25 = malloc(sizeof(int));
    *num25 = 25;
    treeInsertNode(newTree, num25);

    treeDeleteNode(newTree, num25);
    testNumber++;
    printTestInfo(testNumber, "Testing to delete a number to the tree");
    printf("Expect: NULL\n");
    printf("Received: %p\n", (void*)(newTree->root->right));
    testsPassed += printPassFail((newTree->root->right) == NULL);

    temp = treeHasTwoChildren(newTree->root);
    testNumber++;
    printTestInfo(testNumber, "Testing the tree has two children");
    printf("Expect: 0\n");
    printf("Received: %d\n", temp);
    testsPassed += printPassFail(temp == 0);

    num9 = malloc(sizeof(int));
    *num9 = 9;
    treeInsertNode(newTree, num9);

    num11 = malloc(sizeof(int));
    *num11 = 11;
    treeInsertNode(newTree, num11);

    num8 = malloc(sizeof(int));
    *num8 = 8;
    treeInsertNode(newTree, num8);

    num6 = malloc(sizeof(int));
    *num6 = 6;
    treeInsertNode(newTree, num6);

    temp = treeIsEmpty(newTree);
    testNumber++;
    printTestInfo(testNumber, "Testing the tree is empty");
    printf("Expect: 0\n");
    printf("Received: %d\n", temp);
    testsPassed += printPassFail(temp == 0);

    num = treeFindNode(newTree, num10);
    testNumber++;
    printTestInfo(testNumber, "Testing find a node to the tree");
    printf("Expect: %d\n", *num10);
    printf("Received: %d\n", *num);
    testsPassed += printPassFail(num == num10);

    num = treeFindMin(newTree);
    testNumber++;
    printTestInfo(testNumber, "Testing find the min in the tree");
    printf("Expect: %d\n", *num6);
    printf("Received: %d\n", *num);
    testsPassed += printPassFail(num == num6);

    num = treeFindMax(newTree);
    testNumber++;
    printTestInfo(testNumber, "Testing find the max in the tree");
    printf("Expect: %d\n", *num20);
    printf("Received: %d\n", *num);
    testsPassed += printPassFail(num == num20);

    printf("In Order print:");
    treeInOrderPrint(newTree,printNodeFP);
    printf("\nPreorder print:");
    treePreOrderPrint(newTree,printNodeFP);
    printf("\nPost order print:");
    treePostOrderPrint(newTree,printNodeFP);
    printf("\n");

    destroyBalancedBinTree(newTree);

    printf("Testing destroy funtion with valgrind and cppCheck\n");
    printf("The function works well when there is no memory leak reported\n\n");

    printf("The total number of testing: %d\n", testNumber);
    printf("-----The total number of test passed: %d-----\n\n", testsPassed);


    return 0;
}

int compare(void *first,void *second)
{
    int a,b;

    a = *((int*)first);
    b = *((int*)second);

    return a-b;
}

void destroy(void *toBeDeleted)
{
    free(toBeDeleted);
}

void *copy(void *toBeCopy)
{
    int *newPtr;

    newPtr = toBeCopy;

    return newPtr;
}

void printNodeFP(void *data)
{
    printf(" %d", *((int *)data));
}
