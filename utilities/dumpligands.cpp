#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "dumpligands 16_lig.pdbqt 16_hdr.bin 16_idx.csv\n";
		return 0;
	}

	string line;
	size_t p;
	ifstream lig(argv[1]);
	ifstream hdr(argv[2]);
	ifstream idx(argv[3]);
	while (getline(idx, line))
	{
		hdr.seekg(sizeof(p) * stoul(line));
		hdr.read((char*)&p, sizeof(p));
		lig.seekg(p);
		while (getline(lig, line))
		{
			cout << line << '\n';
			if (line[0] == 'T') break;
		}
	}
}
