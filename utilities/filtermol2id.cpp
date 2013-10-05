#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

using std::vector;
using std::string;
using boost::filesystem::path;
using boost::filesystem::ifstream;
using boost::filesystem::ofstream;
using boost::filesystem::directory_iterator;

inline bool starts_with(const string& str, const string& start)
{
	const size_t start_size = start.size();
	if (str.size() < start_size) return false;
	for (size_t i = 0; i < start_size; ++i)
	{
		if (str[i] != start[i]) return false;
	}
	return true;
}

void dump(const vector<string>& lines, const path filename)
{
	const size_t num_lines = lines.size();
	ofstream out(filename);
	for (size_t i = 0; i < num_lines; ++i)
	{
		out << lines[i] << '\n';
	}
	out.close();
}

bool binary(const vector<string>& ids, const string& id)
{
	size_t s = 0;
	size_t e = ids.size();
	while (s + 1 < e)
	{
		const size_t mid = (s + e) / 2;
		if (id < ids[mid])
		{
			e = mid;
		}
		else
		{
			s = mid;
		}
	}
	return (id == ids[s]);
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << "filtermol2 16_folder 16_id_diff.csv\n";
		return 0;
	}

	const path subset = argv[1];
	const path prop = argv[2];

	std::cout << "Reading " << prop << std::endl;
	vector<string> ids;
	ids.reserve(5136507); // Number of molecules in 16_id_diff.csv
	string line;
	ifstream xls(prop);
//	getline(xls, line); // Filter out header line.
	while (getline(xls, line))
	{
		ids.push_back(line);
	}
	xls.close();

	const path mol2_folder = subset / "mol2";
	const string delimiter = "@<TRIPOS>MOLECULE";
	vector<string> lines; // Each molecule takes up <= 300 lines.
	lines.reserve(300);
	string id; // e.g. ZINC00000007
	const directory_iterator end_dir_iter;
	for (directory_iterator dir_iter(subset); dir_iter != end_dir_iter; ++dir_iter)
	{
		if (!is_regular_file(dir_iter->status())) continue;
		const path mol2_file = dir_iter->path();
//		const path mol2_file = subset / "16_p0.0.mol2";
		if (mol2_file.extension() != ".mol2") continue;
		const string slice = mol2_file.stem().string();
		std::cout << slice << std::endl;
		ifstream in(mol2_file);
		while (getline(in, line))
		{
			if (line == delimiter)
			{
				if (!lines.empty())
				{
					if (binary(ids, id.substr(4)))
					{
						dump(lines, mol2_folder / (id + ".mol2"));
					}
					lines.clear();
				}
				lines.push_back(line);
				getline(in, id);
				lines.push_back(id);
			}
			else
			{
				lines.push_back(line);
			}
		}
		in.close();
		if (binary(ids, id))
		{
			dump(lines, mol2_folder / (id + ".mol2"));
		}
		lines.clear();
	}
	return 0;
}
