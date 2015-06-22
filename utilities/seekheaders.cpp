#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "seekheaders 16_lig.pdbqt 16_hdr.bin" << endl;
		return 0;
	}

	string line;
	size_t p;
	ifstream lig(argv[1]);
	ifstream hdr(argv[2]);
	for (size_t i = 0; hdr.read((char*)&p, sizeof(p)); ++i)
	{
		lig.seekg(p);
		getline(lig, line);
		if (line != "ROOT")
		{
			cerr << i << endl;
		}
	}
}
