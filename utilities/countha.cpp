#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "countha 3c2f_ligand.pdbqt\n";
		return 0;
	}

	string line;
	size_t hac = 0;
	for (ifstream ifs(argv[1]); getline(ifs, line);)
	{
		const string record = line.substr(0, 6);
		if ((record == "ATOM  " || record == "HETATM") && (!(line[77] == 'H' && (line[78] == ' ' || line[78] == 'D')))) ++hac;
	}
	cout << hac << endl;
}
