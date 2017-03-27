/*
  Joshua Herrera
  EE 3223   Spring 2017
  Homework 3
*/

#include <iostream>
using namespace std;


void allocate (int&, int, string*&);
int search (string*&, string);


int main() {

string *input = new string[10];
string SearchWord, word;
int size = 10, w = 0; // size to keep track of input array, w is index for input

	
	cout << endl << "Start entering text. Every word in each line will be searched.\nType *end* when finished entering text." << endl << endl;

		while (cin >> word) {
			input[w] = word;
			if (input[w] == "*end*") break;
			w++;
			if (w == (size-1))
				allocate (size, w, input);
		}
		
		cout << endl << "What word would you like to search for?: ";
		cin >> SearchWord;
		cout << endl << "You entered \"" << SearchWord << "\" " << search(input, SearchWord) << " times!" << endl;
				
	return 0;
}


// Function to add space to array if it fills up

void allocate (int& size, const int n, string* &array) {
	size+=10;	
	string *temp = new string[size];
	for (int j = 0; j <= n; j++)
		temp[j] = array[j];
	delete[] array;
	array = temp;
}

int search (string* &array, string SearchWord) {
	int occurances = 0, i;
	for (i = 0; array[i] != "*end*" ; i++)
		if (array[i] == SearchWord) occurances++;
	return occurances;
}
