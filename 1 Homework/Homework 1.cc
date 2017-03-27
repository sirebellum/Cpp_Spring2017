/*
  Joshua Herrera
  EE 3223   Spring 2017
  Homework 1 (case method)
*/

#include<iostream>
using namespace std;

int main() {

//i is the number of characters on the current line
//s is the number of spaces preceding the characters on the current line
int i = 1, s = 5, a , h , j;
char space = ' ', star = '*', hat = '^';


while (i<12) {

//Prints spaces
	for (j=s; j>0; j--) 
		cout << space;
	s--;  //one less space for the next line


//Prints characters. We use i to determine what line we're on, and therefore, what character needs to be printed
	switch (i)  {
		case 1  :
		case 5  :
		case 9  :
			for (a=i; a>0; a--)  //a is the number of astericks
				cout << star;
			cout << "\n";			
			break;
		case 3  :
		case 7	:
		case 11 :
			for (h=i; h>0; h--)  //h is the number of hats
				cout << hat;
			cout << "\n";			
			break;
		}


	i = i+2;

	}

return 0;
}
