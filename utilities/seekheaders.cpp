#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "seekheaders 16_lig.pdbqt 16_hdr.bin\n";
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
		if (line.substr(0, 6) != "REMARK")
		{
			cout << i << endl;
			continue;
		}
		getline(lig, line);
		if (line.substr(0, 6) != "REMARK")
		{
			cout << i << endl;
			continue;
		}
		getline(lig, line);
		if (line.substr(0, 6) != "REMARK")
		{
			cout << i << endl;
			continue;
		}
		if (line.size() == 12) // REMARK     0
		{
			cout << i << endl;
			continue;
		}
	}
}
