#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	double g;
	while (cin.read(reinterpret_cast<char*>(&g), sizeof(g)))
	{
		cout << g << endl;
	}
}
