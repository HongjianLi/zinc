#include <iostream>
#include <string>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

using std::cout;
using std::string;
using std::vector;
using boost::ptr_vector;
using boost::filesystem::path;
using boost::filesystem::directory_iterator;
using boost::filesystem::ifstream;
using boost::filesystem::ofstream;

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

inline bool ends_with(const string& str, const string& end)
{
	const size_t str_size = str.size();
	const size_t end_size = end.size();
	if (str_size < end_size) return false;
	for (size_t i = 1; i <= end_size; ++i)
	{
		if (str[str_size - i] != end[end_size - i]) return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	const directory_iterator end_dir_iter;

	vector<path> slices;
	for (directory_iterator dir_iter("pdbqt"); dir_iter != end_dir_iter; ++dir_iter)
	{
		if (!is_directory(dir_iter->status())) continue;
		slices.push_back(dir_iter->path());
	}
	cout << "Found " << slices.size() << " slices\n";

	path prop;
	for (directory_iterator dir_iter("."); dir_iter != end_dir_iter; ++dir_iter)
	{
		if (!is_regular_file(dir_iter->status())) continue;
		const path p = dir_iter->path();
		if (ends_with(p.string(), "_prop.xls"))
		{
			prop = p;
			break;
		}
	}
	const auto prop_str = prop.string();
	const path idcsv = prop_str.substr(0, prop_str.size() - 4) + "ha.csv";

	cout << "Reading " << prop << '\n';
	string line;
	ifstream in(prop);
	getline(in, line); // Filter out header line.
	ofstream out(idcsv);
	out << line.substr(0, 7) << "\tHA" << line.substr(7) << '\n';
	while (getline(in, line))
	{
		const string id = line.substr(0, 12);
		size_t hac = 0;
		for (const auto& s : slices)
		{
			const path p = s / (id + ".pdbqt");
			if (!exists(p)) continue;
			string l;
			ifstream pdbqt(p);
			while (getline(pdbqt, l))
			{
				if ((starts_with(l, "ATOM  ") || starts_with(l, "HETATM")) && (!((l[77] == 'H') && ((l[78] == ' ') || (l[78] == 'D'))))) ++hac;
			}
			break;
		}
		out << line.substr(0, 12) << '\t' << hac << line.substr(12) << '\n';
	}

	return 0;
}
