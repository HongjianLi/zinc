#include <iostream>
using namespace std;
int main()
{
	string line;
	while (true)
	{
		const size_t p = cin.tellg();
		if (!getline(cin, line)) break;
		if (line.substr(0, 10) == "REMARK 911")
		{
			cout.write((char*)&p, sizeof(p));
		}
	}
}
