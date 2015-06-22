#include <iostream>
using namespace std;
int main()
{
	cout << 0 << endl;
	for (string line; getline(cin, line);)
	{
		if (line == "$$$$")
		{
			cout << cin.tellg() << endl;
		}
	}
}
