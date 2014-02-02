#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void output(const vector<string>& ids, const string& id, const string& ss, vector<string>& lines, ofstream& ofsnid)
{
	if (!binary_search(ids.cbegin(), ids.cend(), id))
	{
		ofsnid << id << ',' << ss << '\n';
		ofstream ofsmol2("16_p0." + ss + ".m/" + id + ".mol2");
		for (const auto& l : lines)
		{
			ofsmol2 << l << '\n';
		}
	}
	lines.clear();
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "filtermol2 16_id.csv begin_slice end_slice\n";
		return 0;
	}

	// Parse 16_id.csv, which is assumed to be sorted.
	string line;
	vector<string> ids;
	ids.reserve(23129083);
	for (ifstream ifs(argv[1]); getline(ifs, line); ids.push_back(line));

	// Filter 16_p0.*.mol2 one by one.
	const size_t beg = stoul(argv[2]);
	const size_t end = stoul(argv[3]);
	vector<string> lines;
	string id;
	for (size_t s = beg; s <= end; ++s)
	{
		const string ss = to_string(s);
		const string slice = "16_p0." + ss;
		cout << slice << endl;
		ofstream ofsnid(slice + ".csv");
		for (ifstream ifs(slice + ".mol2"); getline(ifs, line); lines.push_back(line))
		{
			if (line == "@<TRIPOS>MOLECULE" && lines.size())
			{
				output(ids, id, ss, lines, ofsnid);
			}
			else if (line[0] == 'Z')
			{
				id = line.substr(4); // id is 8 characters wide, without the ZINC prefix.
			}
		}
		output(ids, id, ss, lines, ofsnid);
	}
}
