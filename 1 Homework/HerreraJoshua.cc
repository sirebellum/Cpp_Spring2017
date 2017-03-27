/*
  Joshua Herrera
  EE 3223   Spring 2017
  Homework 1
*/

#include<iostream>
using namespace std;

int main() {

//i is the number of characters on the current line
//s is the number of spaces preceding the characters on the current line
int i = 1, s = 5, a , h , j;
char space = ' ', star = '*', hat = '^';


while (i<11) {

//Prints spaces and then stars
	for (j=s; j>0; j--) 
		cout << space;
	s--;

	for (a=i; a>0; a--)
		cout << star;
	cout << "\n";
	i = i+2;

//Prints spaces and then hats
	for (j=s; j>0; j--) 
		cout << space;
	s--;

	for (h=i; h>0; h--)
		cout << hat;
	cout << "\n";
	i = i+2;

	}

return 0;
}
