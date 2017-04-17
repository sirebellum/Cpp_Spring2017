#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	
	ifstream infile("sudoku1.txt");
	string line;
	
	while (getline(infile, line)) {
		
		istringstream iss(line);
		int row[9];
		for (int i = 0; i<=8; i++)
			if (!(iss >> row[i])) { break; } // error

    for (int i = 0; i<=8; i++)
	   cout << row[i] << " ";
   
	cout << endl;
	}
}