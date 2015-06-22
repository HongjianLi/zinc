#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	for (string line; getline(cin, line);)
	{
		const size_t offset = stoul(line);
		cout.write(reinterpret_cast<const char*>(&offset), sizeof(offset));
	}
}
