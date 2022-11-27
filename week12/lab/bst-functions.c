// Binary search tree insertion code written in the class
#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
  int data;
  struct tree_node *left;
  struct tree_node *right;
} tree_node;

int c = 0;
tree_node *create_node(int val);
void inorder(tree_node *current_ptr);
tree_node *insert(tree_node *root, tree_node *element);

int main(void)
{
  tree_node *my_root = NULL, *temp_node;

  int element;

  printf("Enter a number to insert in the tree: ");
  scanf("%d", &element);

  while (element != 0)
  {
    temp_node = create_node(element); // Create the node.
    // Insert the value.
    my_root = insert(my_root, temp_node);

    printf("In-order traversal: ");
    inorder(my_root);

    printf("\nEnter a number to insert in the tree: ");
    scanf("%d", &element);
  }

  return 0;
}

// take the root of the tree and insert the node element in the tree. Returns the root of the tree

tree_node *insert(tree_node *root, tree_node *element)
{
  if (root == NULL)
    return element;
  else
  {
    if (element->data > root->data)
    {
      if (root->right != NULL)
        root->right = insert(root->right, element);
      else
        root->right = element;
    }
    else
    {
      if (root->left != NULL)
        root->left = insert(root->left, element);
      else
        root->left = element;
    }

    return root;
  }
}

void inorder(tree_node *current_ptr)
{
  if (current_ptr != NULL)
  {
    inorder(current_ptr->left);
    printf("%d ", current_ptr->data);
    inorder(current_ptr->right);
  }
}

// take an integer and return a new node filling up with the integer with left and right pointers as NULL
tree_node *create_node(int val)
{

  // Allocate space for the node, set the fields.
  tree_node *temp;
  temp = (tree_node *)malloc(sizeof(tree_node));
  temp->data = val;
  temp->left = NULL;
  temp->right = NULL;

  return temp; // Return a pointer to the created node.
}

// searching for node in bst
int find(struct tree_node *current, int val)
{
  if (current != NULL)
  {
    if (val == current->data)
      return 1;

    if (val > current->data)
      return find(current->right, val);
    else
      return find(current->left, val);
  }
  else
    return 0;
}

// searching for node in normal tree
int find2(struct tree_node *current, int val)
{
  if (current == NULL)
    return 0;
  else
  {
    if (current->data == val)
      return 1;
    else
      return find2(current->left, val) || find2(current->right, val);
  }
}

// sum all values
int add(struct tree_node *current)
{
  if (current != NULL)
    return current->data + add(current->left) + add(current->right);
  else
    return 0;
}

// count the nodes
int count(struct tree_node *current)
{
  if (current != NULL)
    return 1 + add(current->left) + add(current->right);
  else
    return 0;
}

// count number of leaves
int numLeaves(struct tree_node *p)
{
  if (p == NULL)
    return 0;
  else
  {
    if (p->left == NULL && p->right == NULL)
      return 1;

    return numLeaves(p->left) + numLeaves(p->right);
  }
}

int printEven(struct tree_node *current)
{
  if (current != NULL)
  {
    if (current->data % 2 == 0)
      printf("%d ", current->data);

    printEven(current->right);
    printEven(current->left);
  }
}

// in ascending order
int printOdd(struct tree_node *current)
{
  if (current != NULL)
  {
    printEven(current->left);

    if (current->data % 2 == 1)
      printf("%d ", current->data);

    printEven(current->right);
  }
}

int height(struct tree_node *root)
{
  if (root == NULL)
    return 0;

  int leftHeight = height(root->left);

  int rightHeight = height(root->right);

  // + 1 for root
  if (leftHeight > rightHeight)
    return leftHeight + 1;

  else
    return rightHeight + 1;
}

struct node *largest(struct tree_node *b)
{
  if (b == NULL)
  {
    return NULL;
  }
  else if (b->right == NULL)
  {
    return b;
  }
  else
    return largest(b->right);
}

// number of single children
int singleChildren(struct tree_node *p)
{
  if (p != NULL)
  {
    if (p->left == NULL)
      if (p->right != NULL)
        return 1 + singlechild(p->right);
      else if (p->right == NULL)
      {
        if (p->left != NULL)
          return 1 + singlechild(p->left);
      }
      else
        return singlechild(p->left) + singlechild(p->right);
  }
}
