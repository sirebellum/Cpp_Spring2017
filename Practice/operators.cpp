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
				if (foo.thing1[i+j] != bar[j] && (foo.thing1[i+j] == ' ' || foo.thing1[i+j] == '\0'))
				{
						found = i;
				}
			}
		}
		if (found)
			break;
	}
	
	if (found!=0)
	{
		input nfoo;
		int j = 0;
		for (int i = 0; foo.thing1[i]!='\0'; i++)
		{
			if (i == found)
			{
				j = found;
				while (foo.thing1[i] != ' ' || foo.thing1[i] != '\0')
					i++;
			}
			else
				nfoo.thing1[i] + foo.thing1[i+j];
		}
		nfoo.thing1[0] = '1';
		return nfoo;
	}
	
	else
	{
		foo.thing1[0] = '0';
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