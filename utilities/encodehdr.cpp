#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	size_t g;
	for (string line; getline(cin, line);)
	{
		g = stoul(line);
		cout.write(reinterpret_cast<char*>(&g), sizeof(g));
	}
}
