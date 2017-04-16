#include <iostream>
using namespace std;

// Non-Recursive Functions for TreeNode

struct TreeNode {
  // An object of type TreeNode represents one node
  // in a binary tree of strings.

  string item;      // The data in this node.
  TreeNode * left;    // Pointer to left subtree.
  TreeNode * right;   // Pointer to right subtree.

  TreeNode(string str) {
    // Constructor.  Make a node containing str.
    item = str;
    left = NULL;
    right = NULL;
  }
};  // end struct Treenode

bool treeContains( TreeNode *root, const string item ) {
       // Return true if item is one of the items in the binary
       // sort tree to which root points.   Return false if not.
   if ( root == NULL ) {
         // Tree is empty, so it certainly doesn't contain item.
      return false;
   }
   else if ( item == root->item ) {
         // Yes, the item has been found in the root node.
      return true;
   }
   else if ( item < root->item ) {
         // If the item occurs, it must be in the left subtree.
      return treeContains( root->left, item );
   }
   else {
         // If the item occurs, it must be in the right subtree.
      return treeContains( root->right, item );
   }
}  // end treeContains()

bool treeContainsNR( TreeNode * root, const string item ) {
  // Return true if item is one of the items in the binary
  // sort tree to which root points.   Return false if not.
  TreeNode *runner;  // For "running" down the tree.
  runner = root;     // Start at the root node.
  while (true) {
    if (runner == NULL) {
      // We've fallen off the tree without finding item.
      return false;  
    }
      else if ( item == runner->item ) {
            // We've found the item.
         return true;
      }
      else if ( item < runner->item ) {
            // If the item occurs, it must be in the left subtree,
            // So, advance the runner down one level to the left.
         runner = runner->left;
      }
      else {
            // If the item occurs, it must be in the right subtree.
            // So, advance the runner down one level to the right.
         runner = runner->right;
      }
   }  // end while
} // end treeContains();


void treeInsert(TreeNode * &root, const string newItem) {
  // Add the item to the binary sort tree to which the parameter
  // "root" refers.  Note that root is passed by reference since
  // its value can change in the case where the tree is empty.
  if ( root == NULL ) {
         // The tree is empty.  Set root to point to a new node containing
         // the new item.  This becomes the only node in the tree.
     root = new TreeNode( newItem );
             // NOTE:  The left and right subtrees of root
             // are automatically set to NULL by the constructor.
             // This is important!
     return;
  }
  else if ( newItem < root->item ) {
     treeInsert( root->left, newItem );
  }
  else {
     treeInsert( root->right, newItem );
  }
}  // end treeInsert()



/* Joshua Herrera
   Homework 7 */
//Beginning of student code

void printTree(TreeNode * cur) {
	if (cur != NULL) {
		printTree(cur->left);
		cout << cur->item << endl;
		printTree(cur->right); }
} // end printTree()

TreeNode * searchTree(TreeNode * cur, string item) {
	
	TreeNode * result = NULL;
	
	if (cur != NULL) {
		if (cur->item == item) return cur;
		
		result = searchTree(cur->left, item);
		if (result != NULL) return result;
		
		result = searchTree(cur->right, item); }
	
	return result;
} // end searchTree()

int main(){
	
	TreeNode * root;  // Pointer to the root node in the tree.
	root = NULL;     // Start with an empty tree.
	treeInsert(root, "John");
	treeInsert(root, "Mary");
	treeInsert(root, "Tim");
	treeInsert(root, "Jose");
 	treeInsert(root, "Alice");
  
	printTree(root);
	
	cout << endl;
	
	if (searchTree(root, "Jose") != NULL) cout << "Found" << endl;
 
} 