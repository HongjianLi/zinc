#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<size_t> headers;
	headers.reserve(203965);
	for (string line; getline(cin, line);)
	{
		if (line == "$$$$")
		{
			headers.push_back(cin.tellg());
		}
	}
	const size_t p = 0;
	cout.write(reinterpret_cast<const char*>(&p), sizeof(p));
	cout.write(reinterpret_cast<char*>(headers.data()), sizeof(size_t) * (headers.size() - 1));
}
