#include <iostream>
using namespace std;
int main()
{
	for (string line; true;)
	{
		const size_t p = cin.tellg();
		if (!getline(cin, line))
		{
			cout << p << endl;
			break;
		}
		if (line == "ROOT")
		{
			cout << p << endl;
		}
	}
}
