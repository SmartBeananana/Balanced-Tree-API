/**
 * @file balancedTreeImpl.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing implementation of AVL tree
 */

 #include "balancedTreeAPI.h"

 Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
 {
     Tree *newTree;

     newTree = malloc(sizeof(Tree));

     if(newTree == NULL)
         return NULL;

     newTree->root = NULL;
     newTree->compareFP = compareFP;
     newTree->destroyFP = destroyFP;
     newTree->copyFP = copyFP;

     return newTree;
 }

 TreeNode *createBalancedBinNode(void *data)
 {
     TreeNode *newTreeNode;

     newTreeNode = malloc(sizeof(TreeNode));

     if(newTreeNode == NULL)
         return NULL;

     newTreeNode->data = data;
     newTreeNode->left = NULL;
     newTreeNode->right = NULL;
     newTreeNode->height = 1;

     return newTreeNode;
 }

 void destroyBalancedBinTree(Tree *toBeDeleted)
 {
     if(toBeDeleted == NULL)
         return;

     destroyRecursion(toBeDeleted->root,toBeDeleted);
     free(toBeDeleted);
 }

 void destroyRecursion(TreeNode *theTreeNode, Tree *theTree)
 {
      if(theTree == NULL || theTreeNode == NULL)
         return;

      destroyRecursion(theTreeNode->left, theTree);
      destroyRecursion(theTreeNode->right, theTree);

      theTree->destroyFP(theTreeNode->data);

      free(theTreeNode);
 }

 void treeInsertNode(Tree *theTree, void *toBeInserted)
 {
     if(theTree == NULL || toBeInserted == NULL)
         return;

     TreeNode *newTreeNode;

     newTreeNode = createBalancedBinNode(toBeInserted);

     if(newTreeNode == NULL)
         return;

     theTree->root = treeInsertNodeRecursion(theTree, theTree->root, newTreeNode);
     updateHeight(theTree->root);
 }

 TreeNode *treeInsertNodeRecursion(Tree *theTree,TreeNode *theTreeNode,TreeNode *newTreeNode)
 {
     if(theTreeNode == NULL)
         return newTreeNode;

     if(theTree->compareFP(newTreeNode->data,theTreeNode->data) < 0)
     {
         theTreeNode->left = treeInsertNodeRecursion(theTree,theTreeNode->left,newTreeNode);
     }
     else if(theTree->compareFP(newTreeNode->data,theTreeNode->data) > 0)
     {
         theTreeNode->right = treeInsertNodeRecursion(theTree,theTreeNode->right,newTreeNode);
     }

     updateHeight(theTreeNode);
     if(checkBalance(theTreeNode) < -1)
     {
         if(checkBalance(theTreeNode->right) > 0)
         {
             return rightLeftRotation(theTreeNode);
         }
         else
         {
             return leftRotation(theTreeNode);
         }
     }

     if(checkBalance(theTreeNode) > 1)
     {
         if(checkBalance(theTreeNode->left) < 0)
         {
             return leftRightRotation(theTreeNode);
         }
         else
         {
             return rightRotation(theTreeNode);
         }
     }

     updateHeight(theTreeNode);

     return theTreeNode;
 }

 void treeDeleteNode(Tree *theTree, void *toBeDeleted)
 {
     if(theTree == NULL || toBeDeleted == NULL)
         return;

     theTree->root = treeDeleteNodeRecursion(theTree, theTree->root, toBeDeleted);
 }

 TreeNode *treeDeleteNodeRecursion(Tree *theTree, TreeNode *theTreeNode, void *toBeDeleted)
 {
     if(theTreeNode == NULL)
         return NULL;

     if(theTree->compareFP(toBeDeleted,theTreeNode->data) < 0)
     {
         theTreeNode->left = treeDeleteNodeRecursion(theTree,theTreeNode->left,toBeDeleted);
         updateHeight(theTreeNode);
     }
     else if(theTree->compareFP(toBeDeleted,theTreeNode->data) > 0)
     {
         theTreeNode->right = treeDeleteNodeRecursion(theTree,theTreeNode->right,toBeDeleted);
         updateHeight(theTreeNode);
     }
     else if(theTree->compareFP(toBeDeleted,theTreeNode->data) == 0)
     {
          TreeNode *tempNode = NULL;

          if(theTreeNode->left == NULL && theTreeNode->right == NULL)
          {
               tempNode = NULL;
          }
          else if(theTreeNode->left != NULL && theTreeNode->right == NULL)
          {
               tempNode = theTreeNode->left;
          }
          else if(theTreeNode->left == NULL && theTreeNode->right != NULL)
          {
               tempNode = theTreeNode->right;
          }
          else if(theTreeNode->left != NULL && theTreeNode->right != NULL)
          {
               bottomRight(theTreeNode->left)->right = theTreeNode->right;

               tempNode = theTreeNode->left;
          }
          theTree->destroyFP(theTreeNode->data);
          free(theTreeNode);
          return tempNode;
     }
     return theTreeNode;
 }

 int treeIsEmpty(Tree *theTree)
 {
     if(theTree == NULL || theTree->root == NULL)
         return 1;

     return 0;
 }

 int treeHasTwoChildren(TreeNode *root)
 {
     if(root->left != NULL && root->right != NULL)
         return 1;

     return 0;
 }

 void *treeFindNode(Tree *theTree, void *data)
 {
     if(theTree == NULL)
         return NULL;

     TreeNode *tempNode;

     tempNode = theTree->root;
     while(tempNode)
     {
         if(theTree->compareFP(data,tempNode->data) < 0)
         {
             tempNode = tempNode->left;
         }
         else if(theTree->compareFP(data,tempNode->data) > 0)
         {
             tempNode = tempNode->right;
         }
         else if(theTree->compareFP(data,tempNode->data) == 0)
         {
             return tempNode->data;
         }
     }
     return NULL;
 }

 void *treeFindMin(Tree *theTree)
 {
     if(theTree == NULL || theTree->root == NULL)
         return NULL;

     TreeNode *tempNode;

     tempNode = theTree->root;

     while(tempNode && tempNode->left)
     {
         tempNode = tempNode->left;
     }

     return tempNode->data;
 }

 void *treeFindMax(Tree *theTree)
 {
     if(theTree == NULL || theTree->root == NULL)
         return NULL;

     TreeNode *tempNode;

     tempNode = theTree->root;

     while(tempNode && tempNode->right)
     {
         tempNode = tempNode->right;
     }

     return tempNode->data;
 }

 void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
 {
     if(theTree == NULL || theTree->root == NULL)
         return;

     treeInOrderPrintRecursion(theTree->root,printNodeFP);
 }

 void treeInOrderPrintRecursion(TreeNode *theTreeNode, void (*printNodeFP) (void *data))
 {
     if(theTreeNode == NULL)
         return;

      treeInOrderPrintRecursion(theTreeNode->left,printNodeFP);
      printNodeFP(theTreeNode->data);
      treeInOrderPrintRecursion(theTreeNode->right,printNodeFP);
 }

 void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
 {
     if(theTree == NULL)
         return;

     treePreOrderPrintRecursion(theTree->root,printNodeFP);
 }

 void treePreOrderPrintRecursion(TreeNode *theTreeNode, void (*printNodeFP) (void *data))
{
     if(theTreeNode == NULL)
         return;

     printNodeFP(theTreeNode->data);
     treePreOrderPrintRecursion(theTreeNode->left,printNodeFP);
     treePreOrderPrintRecursion(theTreeNode->right,printNodeFP);
}

 void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
 {
     if(theTree == NULL)
         return;

     treePostOrderPrintRecursion(theTree->root,printNodeFP);
 }

 void treePostOrderPrintRecursion(TreeNode *theTreeNode, void (*printNodeFP) (void *data))
 {
     if(theTreeNode == NULL)
         return;

     treePostOrderPrintRecursion(theTreeNode->left,printNodeFP);
     treePostOrderPrintRecursion(theTreeNode->right,printNodeFP);
     printNodeFP(theTreeNode->data);
 }

 TreeNode *leftRotation(TreeNode *theTreeNode)
 {
     TreeNode *tempNode;

     tempNode = theTreeNode->right;
     theTreeNode->right = tempNode->left;
     tempNode->left = theTreeNode;
     updateHeight(tempNode);
     updateHeight(theTreeNode);

     return tempNode;
 }

 TreeNode *rightRotation(TreeNode *theTreeNode)
 {
     TreeNode *tempNode;

     tempNode = theTreeNode->left;
     theTreeNode->left = tempNode->right;
     tempNode->right = theTreeNode;
     updateHeight(tempNode);
     updateHeight(theTreeNode);

     return tempNode;
 }

 TreeNode *leftRightRotation(TreeNode *theTreeNode)
 {
     theTreeNode->left = leftRotation(theTreeNode->left);

     return rightRotation(theTreeNode);
 }

 TreeNode *rightLeftRotation(TreeNode *theTreeNode)
 {
     theTreeNode->right = rightRotation(theTreeNode->right);

     return leftRotation(theTreeNode);
 }

 int checkBalance(TreeNode *theTreeNode)
 {
     if(theTreeNode == NULL)
     {
         return 0;
     }

     int leftHeight, rightHeight, balance;

     if(theTreeNode->left == NULL)
     {
         leftHeight = 0;
     }
     else
     {
         leftHeight = theTreeNode->left->height;
     }

     if(theTreeNode->right == NULL)
     {
         rightHeight = 0;
     }
     else
     {
         rightHeight = theTreeNode->right->height;
     }

     balance = leftHeight - rightHeight;

     return balance;
 }

 void updateHeight(TreeNode *theTreeNode)
 {
     int leftChild, rightChild;

     if(theTreeNode == NULL)
         return;

     if(theTreeNode->left == NULL)
     {
         leftChild = 0;
     }
     else
     {
         leftChild = theTreeNode->left->height;
     }

     if(theTreeNode->right == NULL)
     {
         rightChild = 0;
     }
     else
     {
         rightChild = theTreeNode->right->height;
     }

     if(leftChild > rightChild)
     {
         theTreeNode->height = leftChild + 1;
     }
     else
     {
         theTreeNode->height = rightChild + 1;
     }

 }

 TreeNode *bottomRight(TreeNode *theTreeNode)
 {

      while(theTreeNode->right)
      {
          theTreeNode = theTreeNode->right;
      }

      return theTreeNode;
 }
