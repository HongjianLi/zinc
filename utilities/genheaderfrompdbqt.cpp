#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<size_t> headers;
	headers.reserve(23129083);
	string line;
	while (true)
	{
		const size_t p = cin.tellg();
		if (!getline(cin, line)) break;
		if (line == "ROOT")
		{
			headers.push_back(p);
		}
	}
	cout.write(reinterpret_cast<char*>(headers.data()), sizeof(size_t) * headers.size());
}
