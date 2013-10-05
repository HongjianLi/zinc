#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::string;
using std::ifstream;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "removehydrogen input.pdbqt\n";
		return 0;
	}

	string line;
	line.reserve(80);
	ifstream in(argv[1]);
	while (getline(in, line))
	{
		if ((line.size() == 79) && (line[77] == 'H') && ((line[78] == ' ') || (line[78] == 'D'))) continue;
		cout << line << '\n';
	}
}
