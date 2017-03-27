#include <iostream>
#include <vector>
using namespace std;

int count(const vector<string>, string (*searchword)());
string prompt_user_for_input();

int main() {
	
	string SearchWord, word;
	vector<string> input;
	string (*prompt)() = prompt_user_for_input;
	int c = 0;
	
	for (int n = 0; word != "*end*"; n++) {
		cin >> word;
		input.push_back(word);
	}

	input.erase(input.end()-1); //Don't need *end* terminator in data

	c = count(input, prompt);

	cout << "Occurances = " << c << endl;

	return 0;

}


int count(const vector<string> input, string (*searchword)()) {
	int occurances = 0;
	int size = input.size();
	string search = (*searchword)();

	for (int i = 0; i<size; i++)
		if (input[i] == search)
			occurances++;

	return occurances;
}

string prompt_user_for_input() {
	string SearchWord;
	cout << endl << "What word?: ";
	cin >> SearchWord;
	return SearchWord;
}