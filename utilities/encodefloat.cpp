#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	float g;
	const auto a = reinterpret_cast<char*>(&g);
	const auto s = sizeof(g);
	for (string line; getline(cin, line);)
	{
		g = stof(line);
		cout.write(a, s);
	}
}
