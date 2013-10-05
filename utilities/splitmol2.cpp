#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void dump(const vector<string>& lines, const string& filename)
{
	ofstream out(filename);
	for (const auto& l : lines)
	{
		out << l << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "splitmol2 input.mol2\n";
		return 0;
	}

	const string delimiter = "@<TRIPOS>MOLECULE";
	vector<string> lines;
	string line, molecule_name;
	for (ifstream in(argv[1]); getline(in, line);)
	{
		if (line == delimiter)
		{
			if (!lines.empty())
			{
				dump(lines, molecule_name + ".mol2");
				lines.clear();
			}
			lines.push_back(delimiter);
			getline(in, molecule_name);
			lines.push_back(molecule_name);
		}
		else
		{
			lines.push_back(line);
		}
	}
	dump(lines, molecule_name + ".mol2");
}

