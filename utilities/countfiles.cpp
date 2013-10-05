#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

using std::vector;
using std::string;
using std::cout;
using boost::filesystem::path;
using boost::filesystem::ifstream;
using boost::filesystem::ofstream;
using boost::filesystem::directory_iterator;

class record
{
public:
	string id, rest;
	vector<string> slices;
	explicit record(string&& id_, string&& rest_) : id(static_cast<string&&>(id_)), rest(static_cast<string&&>(rest_)) {}
	record(const record&) = default;
	record(record&&) = default;
	record& operator=(const record&) = default;
	record& operator=(record&&) = default;
};

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

size_t binary(const vector<record>& records, const string& id)
{
	size_t s = 0;
	size_t e = records.size();
	while (s + 1 < e)
	{
		const size_t mid = (s + e) / 2;
		if (id < records[mid].id)
		{
			e = mid;
		}
		else
		{
			s = mid;
		}
	}
	return s;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "filtermol2 16_folder 16_prop.xls 16_prop.tsv\n";
		return 0;
	}

	const path subset = argv[1];
	const path xls_path = argv[2];
	const path tsv_path = argv[3];

	vector<record> records;
	records.reserve(12171291); // Number of molecules in 16_prop.xls
	string line, header;
	line.reserve(200);

	ifstream xls(xls_path);
	getline(xls, header); // Filter out header line.
	while (getline(xls, line))
	{
		records.push_back(record(line.substr(4, 8), line.substr(13)));
	}
	xls.close();

	const string delimiter = "@<TRIPOS>MOLECULE";
	string id; // e.g. 00000007
	size_t num_mol2s = 0;
	const directory_iterator end_dir_iter;
	for (directory_iterator dir_iter(subset); dir_iter != end_dir_iter; ++dir_iter)
	{
		if (!is_regular_file(dir_iter->status())) continue;
		const path mol2_file = dir_iter->path();
		if (mol2_file.extension() != ".mol2") continue;
		++num_mol2s;
		const string slice = mol2_file.stem().string();
		if (slice[4] != '0') continue;
		const string slice_seg = slice.substr(6);
		cout << num_mol2s << ',' << slice_seg;
		size_t num_molecules = 0, num_molecules_in_prop = 0;
		vector<string> molecules_not_in_prop;
		ifstream in(mol2_file);
		while (getline(in, line))
		{
			if (line == delimiter)
			{
				++num_molecules;
				getline(in, id);
				id = id.substr(4);
				record& r = records[binary(records, id)];
				if (id == r.id)
				{
					r.slices.push_back(slice_seg);
					++num_molecules_in_prop;
				}
				else
				{
					molecules_not_in_prop.push_back(id);
				}
			}
		}
		in.close();
		cout << ',' << num_molecules << ',' << num_molecules_in_prop << ',' << molecules_not_in_prop.size();
		for (auto& s : molecules_not_in_prop) cout << ',' << s;
		cout << '\n';
	}

	ofstream tsv(tsv_path);
	tsv << "Slice\t" << header << '\n';
	for (const auto& r : records)
	{
		const size_t num_slices = r.slices.size();
		if (num_slices == 0) continue;
		if (num_slices > 1) cout << r.id << '\n';
		tsv << r.slices.front() << '\t' << r.id << '\t' << r.rest << '\n';
	}
	tsv.close();

	return 0;
}
