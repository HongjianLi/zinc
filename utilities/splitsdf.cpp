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
	const string delimiter = "$$$$";
	vector<string> lines;
	lines.reserve(300);
	size_t id = 0;
	for (string line; getline(cin, line);)
	{
		lines.push_back(line);
		if (line == delimiter)
		{
			// Dump previous molecule.
			dump(lines, to_string(++id) + ".sdf");
			lines.clear();
		}
	}

	// Dump the last molecule.
	if (lines.size() > 2)
	{
		dump(lines, to_string(++id) + ".sdf");
	}
}

