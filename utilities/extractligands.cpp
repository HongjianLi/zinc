#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "extractligands 16_hdr.bin 16_lig.pdbqt" << endl;
		return 0;
	}

	string line;
	for (ifstream hdr(argv[1]), lig(argv[2]); getline(cin, line);)
	{
		size_t p;
		hdr.seekg(sizeof(p) * stoul(line));
		hdr.read((char*)&p, sizeof(p));
		for (lig.seekg(p); getline(lig, line);)
		{
			cout << line << endl;
			if (line.substr(0, 6) == "TORSDO") break;
		}
	}
}
