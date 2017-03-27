/*
  Joshua Herrera
  EE 3223   Spring 2017
  Homework 2
*/

#include <iostream>
using namespace std;

int main() {

string *input = new string[10];
string SearchWord;
int occurances = 0, n, i, size = 10;
	
	cout << "Start entering words. Enter each word and then press enter. Type *end* when finished." << endl;

	for (n = 0; n >= 0; n++) {
		cin >> input[n];

//Add 10 spots to input array if array gets too big
		if (n == (size-1)) {
			size+=10;			
			string *temp = new string[size];
			for (int j = 0; j <= n; j++)
				temp[j] = input[j];
			delete[] input;
			input = temp;
		}
		
		if (input[n] == "*end*") break;
	}

	n--;
	
	
	cout << "What word would you like to search for?" << endl;
	cin >> SearchWord;
	
	for (i = 0; i <= n; i++)
		if (input[i] == SearchWord) occurances++;
	
	cout << "You entered \"" << SearchWord << "\" " << occurances << " time(s)." << endl;
	
	return 0;
}
