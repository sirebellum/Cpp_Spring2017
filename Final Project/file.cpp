#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	
	ifstream infile("sudoku1.txt");
	string line;
	int board[9][9];
	int r = 0;
	
	while (getline(infile, line)) {
		
		istringstream iss(line);
		for (int j = 0; j<=8; j++)
			if (!(iss >> board[r][j])) { break; } // error
		r++;
	}

	//Print sudoku board with formating
	for (int i = 0; i<=8; i++) {
		for (int j = 0; j<=8; j++)
		{
			cout << board[i][j];
			
			if (j == 2 || j == 5)
				cout << " | ";
			else cout << " ";
			
		}
		cout << endl;
		if (i == 2 || i == 5)
			cout << "----------------------" << endl;
	}
}
