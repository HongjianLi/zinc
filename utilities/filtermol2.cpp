#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void output(const vector<string>& ids, const string& id, vector<string>& lines, ofstream& ofsnid)
{
	if (!binary_search(ids.cbegin(), ids.cend(), id))
	{
		ofsnid << id << '\n';
		ofstream ofsmol2("mol2/" + id + ".mol2");
		for (const auto& l : lines)
		{
			ofsmol2 << l << '\n';
		}
	}
	lines.clear();
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "filtermol2 16_id.csv begin_slice end_slice 16_id_new.csv\n";
		return 0;
	}

	string line;
	vector<string> ids;
	ids.reserve(12171187);
	for (ifstream id(argv[1]); getline(id, line); ids.push_back(line));

	const size_t b = atoi(argv[2]);
	const size_t e = atoi(argv[3]);
	vector<string> lines;
	string id;
	ofstream ofsnid(argv[4]);
	for (size_t s = b; s <= e; ++s)
	{
		cout << s << endl;
		for (ifstream mol2("16_p0." + to_string(s) + ".mol2"); getline(mol2, line); lines.push_back(line))
		{
			if (line == "@<TRIPOS>MOLECULE" && lines.size())
			{
				output(ids, id, lines, ofsnid);
			}
			else if (line[0] == 'Z')
			{
				id = line.substr(4);
			}
		}
		output(ids, id, lines, ofsnid);
	}
}
