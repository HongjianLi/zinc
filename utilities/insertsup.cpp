#include <iostream>
#include <string>
#include <fstream>
#include <boost/tokenizer.hpp>

using namespace std;
using boost::char_separator;
using boost::tokenizer;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "insertprop 16_lig.pdbqt 16_sup.tsv\n";
		return 0;
	}

	const char_separator<char> sep("\t");
	string line;
	line.reserve(80);
	ifstream pdbqt(argv[1]);
	ifstream sup(argv[2]);
	getline(sup, line); // Filter out header line.
	while (getline(pdbqt, line))
	{
		cout << line << '\n';
		if ((line[0] == 'R') && (line[1] == 'E'))
		{
			getline(sup, line);
			cout << "REMARK     ";
			if (line.size() == 1) cout << '0';
			else
			{
				const size_t t = line.find('\t');
				cout << line.substr(0, t);
				const string ss = line.substr(t + 1);
				tokenizer<char_separator<char>> sups(ss, sep);
				for (const auto s : sups) cout << " | " << s;
			}
			cout << '\n';
		}
	}
}
