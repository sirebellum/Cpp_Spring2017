#include<iostream>
using namespace std;

bool compare (char array1[], char array2[]) {
	int sum1 = 0, sum2 = 0;
	for(int i = 0; i < 10; i++)
		sum1+= array1[i];
	for(int i = 0; i < 10; i++)
		sum2+= array2[i];
	
	if (sum1 > sum2)
		return true;
	if (sum1 <= sum2)
		return false;
}

int main() {
	
	int array2[10];
	int array1[10] = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	char test = 'c';
	
	array2[2] = 34;
	
	cout << *(array2+0) << endl;
	cout << *(array2+1) << endl;
	cout << *(array2+2) << endl;
	cout << *(array2+3) << endl;	
	
}


