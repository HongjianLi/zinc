#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	size_t s = 0;
	for (string line; getline(cin, line);)
	{
		s += stoul(line);
		cout << s << endl;
	}
}
