#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	size_t e;
	while (cin.read(reinterpret_cast<char*>(&e), sizeof(e)))
	{
		cout << e << endl;
	}
}
