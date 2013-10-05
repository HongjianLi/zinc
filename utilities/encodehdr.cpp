#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "encodeprop 16_hdr.tsv 16_hdr.bin\n";
		return 0;
	}

	string line;
	ofstream bin(argv[2]);
	for (ifstream tsv(argv[1]); getline(tsv, line);)
	{
		const size_t offset = stoul(line);
		bin.write((char*)&offset, sizeof(offset));
	}
}
