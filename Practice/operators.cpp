#include <iostream>
using namespace std;

class input
{
public:
	char thing1[100];
}; //end input
	

input operator- (input foo, char bar[])
{
	int found = 0;
	
	for (int i = 0; foo.thing1[i]!='\0'; i++)
	{
		if (foo.thing1[i] == bar[0])
		{
			for (int j = 1; bar[j]!='\0'; j++)
			{
				if (foo.thing1[i+j] != bar[j])
				{
					found = 0;
					break;
				}
				else
					found = i;
			}
		}
		if (found != 0)
			break;
	}
	
	if (found!=0)
	{
		input nfoo;
		int j = 0;
		int i = 0;
		for (i; foo.thing1[i+j]!='\0'; i++)
		{
			if (i != found)
				nfoo.thing1[i] = foo.thing1[i+j];
			else
				while (foo.thing1[i+j] != ' ')
					j++;
		}
		nfoo.thing1[i] = '\0';
		return nfoo;
	}
	
	else
	{
		return foo;
	}
}
	

int main()
{
	char thing2[20];
	input thing;
	
	cout << "Enter the first string: ";
	cin.getline(thing.thing1, 100);
	cout << "Enter the word you'd like to remove: ";
	cin.getline(thing2, 20);
	
	input result = thing - thing2;
	
	cout << result.thing1 << endl;
}