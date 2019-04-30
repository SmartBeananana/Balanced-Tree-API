/**
 * @file tree.h
 * @author Xiangyuan Lian & CIS2520
 * @date July 2018
 * @brief File containing implementation of AVL tree
 */
#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_
// #include "balancedTreeAPI.h"

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS.
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;




/*complete the struct definitions.  You can change the existing parts if you wish.
*/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data

  };



struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.

    //Add additional structure elements here
    int height;
};

//add function prototypes as necessary

/**This recursive function destroys a binary tree and all data that is in the tree
 *@param pointer to theTreeNode each node will be deleted
 *@param theTree pointer to binary tree passed by the destroy function
 **/
void destroyRecursion(TreeNode *theTreeNode, Tree *theTree);

/**Recursive function to insert a node into a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param theTreeNode pointer to the node that will be rotated
 *@param newTreeNode pointer to node that is to be inserted into the self-balancing binary tree
 **/
TreeNode *treeInsertNodeRecursion(Tree *theTree,TreeNode *theTreeNode,TreeNode *newTreeNode);

/**Recursive function to insert a node into a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param theTreeNode pointer to the node that will be delete
 *@param toBeDeleted pointer to node that is to be deleted from the self-balancing binary tree
 *@return if successful go through the tree by return the node pointer until the toBeDeleted found
 **/
TreeNode *treeDeleteNodeRecursion(Tree *theTree, TreeNode *theTreeNode, void *toBeDeleted);

/**Recursive function to print a tree in-order.
 *@param theTreeNode pointer to a node in the  self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treeInOrderPrintRecursion(TreeNode *theTreeNode, void (*printNodeFP) (void *data));

/**Recursive function to print a tree in pre-order.
 *@param theTreeNode pointer to a node in the  self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePreOrderPrintRecursion(TreeNode *theTreeNode, void (*printNodeFP) (void *data));

/**Recursive function to print a tree in post-order.
 *@param theTreeNode pointer to a node in the  self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePostOrderPrintRecursion(TreeNode *theTreeNode, void (*printNodeFP) (void *data));

/**Functiont to rotate the tree to the left in order to balance the binary tree
 *@param theTreeNode pointer to the node will be rotated
 *@return the pointer of the node after been rotated
**/
TreeNode *leftRotation(TreeNode *theTreeNode);

/**Functiont to rotate the tree to the right in order to balance the binary tree
 *@param theTreeNode pointer to the node will be rotated
 *@return the pointer of the node after been rotated
**/
TreeNode *rightRotation(TreeNode *theTreeNode);

/**Functiont to do the left-right rotation in order to balance the binary tree
 *@param theTreeNode pointer to the node will be rotated
 *@return the pointer of the node after been rotated
**/
TreeNode *leftRightRotation(TreeNode *theTreeNode);

/**Functiont to do the right-left rotation in order to balance the binary tree
 *@param theTreeNode pointer to the node will be rotated
 *@return the pointer of the node after been rotated
**/
TreeNode *rightLeftRotation(TreeNode *theTreeNode);

/**Function to check the balance of each node
 *@param theTreeNode pointer to the node will be checked
 *@return the integer number of the node balance
**/
int checkBalance(TreeNode *theTreeNode);

/**Function to update the height the node
 *@param theTreeNode pointer the node will be updated the height
**/
void updateHeight(TreeNode *theTreeNode);

/**Function to reach the bottom right node in the binary tree
 *@param theTreeNode pointer to the node in the tree
 *@return pointer to a tree node at the bottom right of the tree 
**/
TreeNode *bottomRight(TreeNode *theTreeNode);


#endif
