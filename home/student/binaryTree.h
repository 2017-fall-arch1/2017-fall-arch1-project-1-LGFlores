#include <string.h>
#include <stdlib.h>

typedef struct tNode{
  /*A bst has two children, need pointers to access them */
  struct tNode* rightChild;
  struct tNode* leftChild;

  char* name;
}tNode;

/*A new node needs to be created in memory, and will return the 
pointer to that new node*/
struct tNode* getNewNode(char* name){

  /*A new node created into memory, will be referenced with
    a pointer to the address*/
  tNode* newNode = (tNode*)malloc(sizeof(tNode));

  newNode -> name = name;
  newNode -> leftChild = NULL;
  newNode -> rightChild = NULL;

  return newNode;
}

struct tNode* insertName(tNode* root, char* name){

  /*An empty tree needs to create a root*/
  if(root == NULL){

    root = getNewNode(name);
  }

  /*Need to find out where to put name, left if less than root's name
   or right of root if greater than root's name*/
  if(strcmp(name,root->name) < 0 ){

    /*Recursion to the left child*/
    root -> leftChild = insertName(root->leftChild,name);
  }

  if( strcmp(name,root->name) > 0){

    root -> rightChild = insertName(root->rightChild,name);
  }

  return root;
}


struct tNode* deleteName(tNode* root, char* name){

  /*Cannot delete name from empty node*/
  if(root == NULL){

    return NULL;
  }

  /*The name is less than the root's name, so search left node*/
  if( strcmp(name,root->name) < 0 ){
   
    root -> leftChild =  deleteName(root->leftChild, name);
  }

  if( strcmp(name,root->name) > 0){

    root -> rightChild = deleteName(root->rightChild,name);
  }

  if( strcmp(name,root->name) == 0){

    /*The node has no children, so the node can be deleted*/ 
    if(root-> leftChild == NULL && root-> rightChild == NULL){

      /*Freeing the root from memory and need to set to null
       so that the parent knows it has no children nodes*/
      free(root);
      root = NULL;
      return root;
    }

    if(root-> rightChild == NULL){

      /*Temp  variable to point to root and setting the left child to be
       the new root*/
      struct tNode* temp = root;
      root = root -> leftChild;
      free(temp);
      return root;
    }

    if(root -> leftChild == NULL){

      struct tNode* temp = root;
      root = root -> rightChild;
      free(temp);
      return root;
    }

    /*The node has two children, so will find the smallest child
     of the right children to promote to the new node*/
    else{

      
      tNode* temp = root;
      
      /*Once null is reached, the tree has no more left children*/
      while(temp -> leftChild != NULL){
	temp = temp ->leftChild;
      }
      /*The old root is replaced with the smalest child on the right side*/
      root -> name = temp -> name;
      root -> rightChild = deleteName(root -> rightChild, temp -> name);
      return root;
    }
  }
}
