#include <iostream>
#include <vector>
using namespace std;

class Node{
  private:
    int val;
    Node* left;
    Node* right;

  public:
    Node();
    Node(int);
    bool set_left(Node*);
    Node* get_left();
    bool set_right(Node*);
    Node* get_right();
    int get_val();
    bool set_val(int);
};

Node::Node() {
  val = 0;
  left = right = NULL;
}

Node::Node(int v) {
  val = v;
  left = right = NULL;
}

bool Node::set_left(Node* n) {
  left = n;
  return true;
}

bool Node::set_right(Node* n) {
  right = n;
  return true;
}

Node* Node::get_left() {
  return left;
}

Node* Node::get_right() {
  return right;
}

int Node::get_val() {
  return val;
}

bool Node::set_val(int v ){
  val = v;
  return true;
}

class BST {
  private:
    Node* root;
    void preorder(Node*);
    void cleanUp(Node*);

  public:
    BST();
    ~BST();
    bool add(int);
    bool is_present(int);
    void display();

    //implement these functions

    //part (a)
      //(10 points) Implement a function called void add_from_array(int*
      //arr, int sz) that takes every element from the input array arr
      //(which is of size sz), and adds it to the tree.
    void add_from_array(int*,int);

    //part (b)
      //(10 points) Implement a function called bool add_all(vector<int>& v)
      //that adds all elements from v to the tree. Return true if all
      //elements were added successfully. False otherwise (e.g., when v
      //contains duplicates).
    bool add_all(vector<int>&);

    //part (c)
      //(10 points) Re-implement display functions as follows:
      //Modify the class design of the Node so that you can keep
      //track of the number of times each number in the tree is checked for
      //presence (that is, the number of times is_present is called for each
      //value in the tree). Re-implement the display function to show this count 
      //for each node, in addition to the content of each node.

    //part (d)
      //(20 points) Implement a function called 
      //int count_greater_than(int v) that returns the number of values in the tree 
      //that is greater than v. Do not modify the existing add function.
    int count_greater_than(int);
};

BST::BST(){
  root=NULL;
}

BST::~BST(){
  cout << "deleting..." << endl;
  cleanUp(root);
  cout << endl;
}

void BST::cleanUp(Node* curr){
  if (curr!=NULL){
    cleanUp(curr->get_left());
    cleanUp(curr->get_right());
    cout << curr->get_val() << " ";
    delete curr;
  }
}

int BST::count_greater_than(int v)
{
	Node* curr=root;
	int num = 0;
	
	if (curr!=NULL){
		preorder(curr->get_left());
		cout << curr->get_val() << " ";
		preorder(curr->get_right());
	}
	}
	return num;
}

void BST::add_from_array(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		add(arr[i]);
}

bool BST::add_all(vector<int>& vect)
{
	bool all = true;
	for (int i = 0; i < vect.size(); i++)
		all&= add(vect[i]);
	
	return all;
}

bool BST::add(int v){
  Node* temp=new Node(v);
  if (root==NULL){
    root=temp;
    return true;
  }
  Node* curr=root;

  while(curr!=NULL){
    if (curr->get_val()==v){
		delete temp;
		return false;
    }
    else if (v < curr->get_val()){
		if (curr->get_left()==NULL){
			curr->set_left(temp);
			return true;
      }
		else
			curr=curr->get_left();
    }
    else{
		if (curr->get_right()==NULL){
			curr->set_right(temp);
			return true;
      }
		else
			curr=curr->get_right();
    }
  }
}

bool BST::is_present(int v){
  Node* curr=root;

  while(curr!=NULL){
    if (curr->get_val()==v)
      return true;
    else if (v > curr->get_val())
      curr = curr->get_right();
    else
      curr = curr ->get_left();
  }
  return false;
}

void BST::display(){
  preorder(root);
  cout << endl;
}

void BST::preorder(Node* curr){
  if (curr!=NULL){
    preorder(curr->get_left());
	cout << curr->get_val() << " ";
    preorder(curr->get_right());
  }
}

int main(){
  BST b;
  int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  vector<int> vect = {12, 13, 14};
  b.add(20);
  b.add(25);
  b.add(15);
  b.add(10);
  b.add(18);
  b.add_from_array(array, 10);
  cout << b.add_all(vect) << endl;
  cout << b.count_greater_than(1) << endl;
  b.display();
  //test your new functionalities here
}
