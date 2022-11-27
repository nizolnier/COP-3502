/* COP 3502C Assignment 4
This program is written by: Nicole Nascimento */
// preprocessor derivatives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"
#define MAXLEN 30

// structs provided :)
typedef struct itemNode
{
  char name[MAXLEN];
  int count;
  struct itemNode *left, *right;
} itemNode;

typedef struct treeNameNode
{
  char treeName[MAXLEN];
  struct treeNameNode *left, *right;
  itemNode *theTree;
} treeNameNode;

// create, build, insert and search from treeName
treeNameNode *createTreeNameNode();
treeNameNode *buildNameTree(int n);
treeNameNode *insertTreeNameNode(treeNameNode *root, treeNameNode *element);
treeNameNode *searchNameNode(treeNameNode *root, char treeName[]);

// delete name function + its auxiliary functions
treeNameNode *deleteName(treeNameNode *root, char treeName[]);
treeNameNode *parentName(treeNameNode *root, treeNameNode *node);
treeNameNode *minName(treeNameNode *root);
int isLeafName(treeNameNode *node);
int hasOnlyLeftChildName(treeNameNode *node);
int hasOnlyRightChildName(treeNameNode *node);

// create, build, insert and search for itemNode
itemNode *createItemNode();
treeNameNode *buildItemTree(treeNameNode *mother, int i);
itemNode *insertItemNode(itemNode *root, itemNode *element);
itemNode *searchItem(itemNode *root, char item[]);

// function to delete theTree from a treeNameNode
itemNode *deleteEntireTree(itemNode *root);

// delete item + auxiliary functions
itemNode *deleteItem(itemNode *root, char item[]);
itemNode *parentItem(itemNode *root, itemNode *node);
itemNode *minItem(itemNode *root);
int isLeafItem(itemNode *node);
int hasOnlyLeftChildItem(itemNode *node);
int hasOnlyRightChildItem(itemNode *node);

// traverse functions
void traverse(treeNameNode *root);
void traverse_in_traverse(treeNameNode *root);
void traverseItems(itemNode *root);

// function that handles queries to keep main clean
void handleQueries(treeNameNode *mother, int q);

// easy functions
int count(itemNode *root);
int height(itemNode *root);
// except for this one
int itemBefore(itemNode *root, char item[]);

// function to free the trees #greenpeace
void freeEverything(treeNameNode *root);

int main(void)
{
  // memory leak report
  atexit(report_mem_leak);
  // n is number of tress, i is number of items and q is number of queries
  int n, i, q;
  // scanning them in
  scanf("%d %d %d", &n, &i, &q);

  // building the bst of bst's (aka the mom)
  treeNameNode *motherOfAllTrees = buildNameTree(n);
  // filling the mom with grandchildren
  motherOfAllTrees = buildItemTree(motherOfAllTrees, i);
  // traversing all trees
  traverse(motherOfAllTrees);
  traverse_in_traverse(motherOfAllTrees);
  printf("\n");
  fprintf(stderr, "\n");
  // calling handleQueries
  handleQueries(motherOfAllTrees, q);

  // freeing the trees
  freeEverything(motherOfAllTrees);

  return 0;
}

// function that malloc's a treeNameNode, fills it with data and returns the pointer
treeNameNode *createTreeNameNode()
{
  // mallocing
  treeNameNode *temp = (treeNameNode *)malloc(sizeof(treeNameNode));

  // filling with data
  scanf("%s", temp->treeName);
  // everything starts at NULL
  temp->left = NULL;
  temp->right = NULL;
  temp->theTree = NULL;

  // returning
  return temp;
}

// function that takes the root of a bst and a new element and inserts the element in to the tree
// this is basically ahmed's code
// only difference is when strcmp is < 0, we insert to right
// strcmp > 0 we insert to left
treeNameNode *insertTreeNameNode(treeNameNode *root, treeNameNode *element)
{
  if (root == NULL)
  {
    return element;
  }
  else
  {
    if (strcmp(root->treeName, element->treeName) < 0)
    {
      if (root->right != NULL)
        root->right = insertTreeNameNode(root->right, element);
      else
        root->right = element;
    }
    else
    {
      if (root->left != NULL)
        root->left = insertTreeNameNode(root->left, element);
      else
        root->left = element;
    }

    return root;
  }
}

// function that builds a bst of treeNameNodes
treeNameNode *buildNameTree(int n)
{
  // set root to NULL at the beginning
  treeNameNode *baby, *root = NULL;
  for (int i = 0; i < n; i++)
  {
    // fill baby
    baby = createTreeNameNode();
    // insert baby
    root = insertTreeNameNode(root, baby);
  }

  // return the root
  return root;
}

// function that takes the root of a treeNameNode bst, and a name and searchs for the name in the tree
// same thing as ahmed's code, but with strcmp
// so strcmp == 0 - it means we found the tree
// strcmp > 0 search left
// strcmp < 0 search right
treeNameNode *searchNameNode(treeNameNode *root, char treeName[])
{
  if (root != NULL)
  {
    if (strcmp(root->treeName, treeName) == 0)
      return root;

    if (strcmp(root->treeName, treeName) > 0)
      return searchNameNode(root->left, treeName);
    else
      return searchNameNode(root->right, treeName);
  }
  else
    return NULL;
}

// function that takes the root of the treeNameNode bst and a treeName and deletes the node
// basically ahmed's code, still with original comments lol
treeNameNode *deleteName(treeNameNode *root, char treeName[])
{
  treeNameNode *delnode, *new_del_node, *save_node;
  treeNameNode *par;

  delnode = searchNameNode(root, treeName); // Get a pointer to the node to delete.

  par = parentName(root, delnode); // Get the parent of this node.

  // Take care of the case where the node to delete is a leaf node.
  if (isLeafName(delnode))
  { // case 1

    // Deleting the only node in the tree.
    if (par == NULL)
    {
      free(root); // free the memory for the node.
      return NULL;
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->treeName, delnode->treeName) > 0)
    {
      free(par->left); // Free the memory for the node.
      par->left = NULL;
    }

    // Deletes the node if it's a right child.
    else
    {
      free(par->right); // Free the memory for the node.
      par->right = NULL;
    }

    return root; // Return the root of the new tree.
  }
  // Take care of the case where the node to be deleted only has a left
  // child.
  if (hasOnlyLeftChildName(delnode))
  {

    // Deleting the root node of the tree.
    if (par == NULL)
    {
      save_node = delnode->left;
      free(delnode);    // Free the node to delete.
      return save_node; // Return the new root node of the resulting tree.
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->treeName, delnode->treeName) > 0)
    {
      save_node = par->left;       // Save the node to delete.
      par->left = par->left->left; // Readjust the parent pointer.
      free(save_node);             // Free the memory for the deleted node.
    }

    // Deletes the node if it's a right child.
    else if (strcmp(par->treeName, delnode->treeName) < 0)
    {
      save_node = par->right;        // Save the node to delete.
      par->right = par->right->left; // Readjust the parent pointer.
      free(save_node);               // Free the memory for the deleted node.
    }

    return root; // Return the root of the tree after the deletion.
  }

  // Takes care of the case where the deleted node only has a right child.
  if (hasOnlyRightChildName(delnode))
  {

    // Node to delete is the root node.
    if (par == NULL)
    {
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }

    // Delete's the node if it is a left child.
    if (strcmp(par->treeName, delnode->treeName) > 0)
    {
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    }

    // Delete's the node if it is a right child.
    else if (strcmp(par->treeName, delnode->treeName) < 0)
    {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }
  // if your code reaches hear it means delnode has two children
  //  Find the new physical node to delete.
  new_del_node = minName(delnode->right);
  char save_name[MAXLEN];
  strcpy(save_name, new_del_node->treeName);

  deleteName(root, save_name); // Now, delete the proper value.

  // Restore the data to the original node to be deleted.
  strcpy(delnode->treeName, save_name);

  return root;
}

// function that deletes an entire itemNode tree by deleting the leftmost item each recursive call
itemNode *deleteEntireTree(itemNode *root)
{
  if (root != NULL)
  {
    // find leftmost item
    itemNode *delnode = minItem(root);
    // delete it
    root = deleteItem(root, delnode->name);
    // do it again
    root = deleteEntireTree(root);
  }

  return root;
}

// function that malloc's an itemNode, fills it with data and returns pointer
itemNode *createItemNode()
{
  // mallocing
  itemNode *temp = (itemNode *)malloc(sizeof(itemNode));

  // filling the data
  scanf("%s %d", temp->name, &temp->count);
  // right and left start at NULL
  temp->left = NULL;
  temp->right = NULL;

  // returning it
  return temp;
}


// function that takes the bst of bst and an integer and fills the tree with itemNodes
treeNameNode *buildItemTree(treeNameNode *mother, int i)
{
  for (int j = 0; j < i; j++)
  {
    // scan the name of the tree to insert the item
    char treeName[MAXLEN];
    scanf("%s", treeName);
    // search the bst of bst for the tree
    treeNameNode *child = searchNameNode(mother, treeName);

    // create the baby item node
    itemNode *baby = createItemNode();

    // isert the baby into the child tree
    // now that I think about it, these were not very good names
    child->theTree = insertItemNode(child->theTree, baby);
  }

  // return the bst of bst
  return mother;
}

// function that takes the root of itemNode bst and a new element and inserts the element in to the tree
// ahmed's code again
itemNode *insertItemNode(itemNode *root, itemNode *element)
{
  if (root == NULL)
  {
    return element;
  }
  else
  {
    if (strcmp(root->name, element->name) < 0)
    {
      if (root->right != NULL)
        root->right = insertItemNode(root->right, element);
      else
        root->right = element;
    }
    else
    {
      if (root->left != NULL)
        root->left = insertItemNode(root->left, element);
      else
        root->left = element;
    }
  }

  return root;
}

// function that takes the root of an itemNode tree and an item and searchs for the item
// same logic as searchNameNode
itemNode *searchItem(itemNode *root, char item[])
{
  if (root != NULL)
  {
    if (strcmp(root->name, item) == 0)
      return root;

    if (strcmp(root->name, item) > 0)
      return searchItem(root->left, item);

    else
      return searchItem(root->right, item);
  }

  else
    return NULL;
}

// function that takes the root of an itemNode tree and an item and deletes the item
// ahmed's code
itemNode *deleteItem(itemNode *root, char item[])
{
  itemNode *delnode, *new_del_node, *save_node;
  itemNode *par;

  delnode = searchItem(root, item); // Get a pointer to the node to delete.

  par = parentItem(root, delnode); // Get the parent of this node.

  // Take care of the case where the node to delete is a leaf node.
  if (isLeafItem(delnode))
  { // case 1

    // Deleting the only node in the tree.
    if (par == NULL)
    {
      free(root); // free the memory for the node.
      return NULL;
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->name, delnode->name) > 0)
    {
      free(par->left); // Free the memory for the node.
      par->left = NULL;
    }

    // Deletes the node if it's a right child.
    else
    {
      free(par->right); // Free the memory for the node.
      par->right = NULL;
    }

    return root; // Return the root of the new tree.
  }

  // Take care of the case where the node to be deleted only has a left
  // child.
  if (hasOnlyLeftChildItem(delnode))
  {

    // Deleting the root node of the tree.
    if (par == NULL)
    {
      save_node = delnode->left;
      free(delnode);    // Free the node to delete.
      return save_node; // Return the new root node of the resulting tree.
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->name, delnode->name) > 0)
    {
      save_node = par->left;       // Save the node to delete.
      par->left = par->left->left; // Readjust the parent pointer.
      free(save_node);             // Free the memory for the deleted node.
    }

    // Deletes the node if it's a right child.
    else if (strcmp(par->name, delnode->name) < 0)
    {
      save_node = par->right;        // Save the node to delete.
      par->right = par->right->left; // Readjust the parent pointer.
      free(save_node);               // Free the memory for the deleted node.
    }

    return root; // Return the root of the tree after the deletion.
  }

  // Takes care of the case where the deleted node only has a right child.
  if (hasOnlyRightChildItem(delnode))
  {

    // Node to delete is the root node.
    if (par == NULL)
    {
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }

    // Delete's the node if it is a left child.
    if (strcmp(par->name, delnode->name) > 0)
    {
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    }

    // Delete's the node if it is a right child.
    else if (strcmp(par->name, delnode->name) < 0)
    {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }
  // if your code reaches hear it means delnode has two children
  //  Find the new physical node to delete.
  char save_name[MAXLEN];
  int save_count;
  new_del_node = minItem(delnode->right);
  save_count = new_del_node->count;
  strcpy(save_name, new_del_node->name);

  deleteItem(root, save_name); // Now, delete the proper value.

  // Restore the data to the original node to be deleted.
  delnode->count = save_count;
  strcpy(delnode->name, save_name);

  return root;
}

// function that traverses the treeNameNode in inorder
void traverse(treeNameNode *root)
{
  if (root != NULL)
  {
    traverse(root->left);
    printf("%s ", root->treeName);
    fprintf(stderr, "%s ", root->treeName);
    traverse(root->right);
  }
}

// function that traverses a treeNameNode and their items in inorder
void traverse_in_traverse(treeNameNode *root)
{
  if (root != NULL)
  {
    traverse_in_traverse(root->left);
    printf("\n===%s===\n", root->treeName);
    fprintf(stderr, "\n===%s===\n", root->treeName);
    traverseItems(root->theTree);
    traverse_in_traverse(root->right);
  }
}

// function that traverses an itemNode in inorder
void traverseItems(itemNode *root)
{
  if (root != NULL)
  {
    traverseItems(root->left);
    printf("%s ", root->name);
    fprintf(stderr, "%s ", root->name);
    traverseItems(root->right);
  }
}

// function that handles all the queries
// we have: search, item_before, height_balance, count, reduce, delete and delete_name
void handleQueries(treeNameNode *mother, int q)
{
  char command[MAXLEN], tree[MAXLEN], item[MAXLEN];

  for (int i = 0; i < q; i++)
  {
    // scan the command
    scanf("%s", command);
    // compare to our list of commands
    // search is pretty straight to the point
    if (strcmp(command, "search") == 0)
    {
      scanf("%s %s", tree, item);
      treeNameNode *foundTree = searchNameNode(mother, tree);

      if (foundTree == NULL)
      {
        printf("%s does not exist\n", tree);
        fprintf(stderr, "%s does not exist\n", tree);
      }
      else
      {
        itemNode *foundItem = searchItem(foundTree->theTree, item);

        if (foundItem == NULL)
        {
          printf("%s not found in %s\n", item, tree);
          fprintf(stderr, "%s not found in %s\n", item, tree);
        }
        else
        {
          printf("%d %s found in %s\n", foundItem->count, item, tree);
          fprintf(stderr, "%d %s found in %s\n", foundItem->count, item, tree);
        }
      }
    }
    else if (strcmp(command, "item_before") == 0)
    {
      // scan tree and item
      scanf("%s %s", tree, item);
      // search for the free
      treeNameNode *foundTree = searchNameNode(mother, tree);

      // call itemBefore with tree and item
      int before = itemBefore(foundTree->theTree, item);

      // print
      printf("item before %s: %d\n", item, before);
      fprintf(stderr, "item before %s: %d\n", item, before);
    }
    else if (strcmp(command, "height_balance") == 0)
    {
      // scan tree and search for it
      scanf("%s", tree);
      treeNameNode *foundTree = searchNameNode(mother, tree);

      // get heights from both sides
      int leftHeight = height(foundTree->theTree->left);
      int rightHeight = height(foundTree->theTree->right);
      // calculate the difference in height (always positive)
      int diff = abs(leftHeight - rightHeight);

      // print
      printf("%s: left height %d, right height %d, difference %d, ", tree, leftHeight, rightHeight, diff);
      fprintf(stderr, "%s: left height %d, right height %d, difference %d, ", tree, leftHeight, rightHeight, diff);
      // display if balanced or not
      if (diff <= 1)
      {
        printf("balanced\n");
        fprintf(stderr, "balanced\n");
      }
      else
      {
        printf("not balanced\n");
        fprintf(stderr, "not balanced\n");
      }
    }
    else if (strcmp(command, "count") == 0)
    {
      // scan the tree and search for it
      scanf("%s", tree);
      treeNameNode *foundTree = searchNameNode(mother, tree);

      // get sum of count
      int total = count(foundTree->theTree);

      // print
      printf("%s count %d\n", tree, total);
      fprintf(stderr, "%s count %d\n", tree, total);
    }
    else if (strcmp(command, "reduce") == 0)
    {
      int num;
      // scan tree, item and number to reduce the count in
      scanf("%s %s %d", tree, item, &num);

      // search for tree and item
      treeNameNode *foundTree = searchNameNode(mother, tree);
      itemNode *foundItem = searchItem(foundTree->theTree, item);
      // update count
      foundItem->count -= num;

      // print
      printf("%s reduced\n", item);
      fprintf(stderr, "%s reduced\n", item);

      // if the count is negative, the item no longer exists
      if (foundItem->count <= 0)
        foundTree->theTree = deleteItem(foundTree->theTree, item);
    }
    else if (strcmp(command, "delete") == 0)
    {
      // deletes an item from the treeNameNode

      scanf("%s %s", tree, item);
      treeNameNode *foundTree = searchNameNode(mother, tree);
      foundTree->theTree = deleteItem(foundTree->theTree, item);

      printf("%s deleted from %s\n", item, tree);
      fprintf(stderr, "%s deleted from %s\n", item, tree);
    }
    else if (strcmp(command, "delete_name") == 0)
    {
      // this one deletes an entire treeNameNode
      // find the tree
      scanf("%s", tree);
      treeNameNode *foundTree = searchNameNode(mother, tree);
      // delete their little kids :(
      foundTree->theTree = deleteEntireTree(foundTree->theTree);

      // go the bst of bst and delete the treeNameNode
      mother = deleteName(mother, tree);

      // print
      printf("%s deleted\n", tree);
      fprintf(stderr, "%s deleted\n", tree);
    }
  }
}

// function that sums up all the count variable from all the items in a tree
// basically code from lab
int count(itemNode *root)
{
  if (root != NULL)
    return root->count + count(root->left) + count(root->right);
  else
    return 0;
}

// function that calculates the height of a itemNode tree
// code from lab :)
int height(itemNode *root)
{
  // tree with no nodes is -1
  if (root == NULL)
    return -1;

  int leftHeight = height(root->left);
  int rightHeight = height(root->right);

  // + 1 for root
  if (leftHeight > rightHeight)
    return leftHeight + 1;

  else
    return rightHeight + 1;
}

// function that returns how many items come before the item's name
int itemBefore(itemNode *root, char item[])
{
  // base case
  if (root == NULL)
    return 0;

  // root is after item
  if (strcmp(root->name, item) >= 0)
    return itemBefore(root->left, item) + itemBefore(root->right, item);

  // root is before item
  if (strcmp(root->name, item) < 0)
    return itemBefore(root->left, item) + itemBefore(root->right, item) + 1;
}


// ----- auxiliary delete functions, so many of them oof
treeNameNode *parentName(treeNameNode *root, treeNameNode *node)
{
  // Take care of NULL cases.
  if (root == NULL || strcmp(root->treeName, node->treeName) == 0)
    return NULL;

  // The root is the direct parent of node.
  if (root->left != NULL && strcmp(root->left->treeName, node->treeName) == 0)
    return root;
  if (root->right != NULL && strcmp(root->right->treeName, node->treeName) == 0)
    return root;

  // Look for node's parent in the left side of the tree.
  if (strcmp(root->treeName, node->treeName) > 0)
    return parentName(root->left, node);

  // Look for node's parent in the right side of the tree.
  else if (strcmp(root->right->treeName, node->treeName) < 0)
    return parentName(root->right, node);

  return NULL; // Catch any other extraneous cases.
}

treeNameNode *minName(treeNameNode *root)
{
  // Root stores the minimal value.
  if (root->left == NULL)
    return root;

  // The left subtree of the root stores the minimal value.
  else
    return minName(root->left);
}

int isLeafName(treeNameNode *node)
{
  return (node->left == NULL && node->right == NULL);
}

int hasOnlyLeftChildName(treeNameNode *node)
{
  return (node->left != NULL && node->right == NULL);
}

int hasOnlyRightChildName(treeNameNode *node)
{
  return (node->left == NULL && node->right != NULL);
}

itemNode *parentItem(itemNode *root, itemNode *node)
{
  // Take care of NULL cases.
  if (root == NULL || strcmp(root->name, node->name) == 0)
    return NULL;

  // The root is the direct parent of node.
  if (root->left != NULL && strcmp(root->left->name, node->name) == 0)
    return root;
  if (root->right != NULL && strcmp(root->right->name, node->name) == 0)
    return root;

  // Look for node's parent in the left side of the tree.
  if (strcmp(root->name, node->name) > 0)
    return parentItem(root->left, node);

  // Look for node's parent in the right side of the tree.
  else
    return parentItem(root->right, node);

  return NULL; // Catch any other extraneous cases.
}

itemNode *minItem(itemNode *root)
{
  // Root stores the minimal value.
  if (root->left == NULL)
    return root;

  // The left subtree of the root stores the minimal value.
  else
    return minItem(root->left);
}

int isLeafItem(itemNode *node)
{
  return (node->left == NULL && node->right == NULL);
}

int hasOnlyLeftChildItem(itemNode *node)
{
  return (node->left != NULL && node->right == NULL);
}

int hasOnlyRightChildItem(itemNode *node)
{
  return (node->left == NULL && node->right != NULL);
}

// function that deletes remaining itemNodes and frees the treeNameNode pointers 
void freeEverything(treeNameNode *root)
{
  if (root != NULL)
  {
    root->theTree = deleteEntireTree(root->theTree);
    freeEverything(root->left);
    freeEverything(root->right);
    free(root);
  }
}
