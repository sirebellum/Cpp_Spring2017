#include <iostream>
#include <vector>
using namespace std;

void make_index(int array[], int arraysize, vector<int> &indx);
void add(int array[], int arraysize, vector<int> &indx, vector<int> &count);

int main () {
	
	int array[20] = {1, 2, 1, 2, 1, 3, 5, 4, 4, 0, 6, 1, 7, 3, 10, 1, 4, 2, 0, 20};
	int arraysize = 20;
	vector<int> indx(array, array+arraysize);
	vector<int> count;
	
	make_index(array, arraysize, indx);
	
	count.resize(indx.size());
	
	add(array, arraysize, indx, count);
	
	for (int i = 0; i < indx.size(); i++)
		cout << "The frequency of " << indx[i] << " is " << count[i] << endl;
}


void make_index(int array[], int arraysize, vector<int> &indx) {
	
//	for (int i = 0; i < arraysize; i++) {
//		indx.push_back(array[i]);
//	}
	
	cout << indx.size() << endl;
	
	for (int i = 0; i < indx.size(); i++)
		for (int j = i+1; j < indx.size(); j++)
			if (indx[i] == indx[j])
				indx.erase(indx.begin()+j);
	
	cout << indx.size() << " " << indx[indx.size()-1] << endl;

}

void add(int array[], int arraysize, vector<int> &indx, vector<int> &count) {
	for (int i = 0; i < indx.size(); i++)
		for (int j = 0; j < arraysize; j++)
			if (indx[i] == array[j])
				count[i]++;
}