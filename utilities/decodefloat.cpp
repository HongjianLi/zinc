#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	float g;
	const auto a = reinterpret_cast<char*>(&g);
	const auto s = sizeof(g);
	while (cin.read(a, s))
	{
		cout << g << endl;
	}
}
