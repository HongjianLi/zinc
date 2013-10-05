#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void dump(const vector<string>& lines, const string& filename)
{
	const size_t num_lines = lines.size();
	ofstream out(filename);
	for (size_t i = 0; i < num_lines; ++i)
	{
		out << lines[i] << endl;
	}
	out.close();
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "splitsdf all.sdf\n";
		return 0;
	}

	const string delimiter = "$$$$";
	const string drugbank_name_record = "> <DRUGBANK_ID>";
	vector<string> lines;
	lines.reserve(300);
	string line, molecule_name;
	for (ifstream in(argv[1]); getline(in, line);)
	{
		if (line == delimiter)
		{
			// Dump previous molecule.
			dump(lines, molecule_name + ".sdf");
			lines.clear();
		}
		else
		{
			lines.push_back(line);
			if (line == drugbank_name_record)
			{
				getline(in, line);
				lines.push_back(line);
				molecule_name = line;
			}
		}
	}

	// Dump the last molecule.
	if (lines.size() > 2)
	{
		dump(lines, molecule_name + ".sdf");
	}

	return 0;
}

