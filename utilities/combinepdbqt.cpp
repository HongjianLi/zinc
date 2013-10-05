#include <iostream>
#include <string>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

using std::cout;
using std::string;
using std::vector;
using std::logic_error;
using boost::ptr_vector;
using boost::lexical_cast;
using boost::filesystem::path;
using boost::filesystem::ifstream;
using boost::filesystem::ofstream;
using boost::filesystem::directory_iterator;
using boost::filesystem::canonical;

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

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "combinepdbqt pdbqt_folder out_folder start_slice\n";
		return 0;
	}

	const size_t step = 1000;
	const string remark = "REMARK ";
	const string torsdof = "TORSDOF ";
	vector<string> ids;
	ids.reserve(13000000);
	string line;
	line.reserve(80);
/*
	cout << "Iterating pdbqt files\n";
	size_t milestone = step;
	const path pdbqt_folder = argv[1];
	const directory_iterator end_dir_iter;
	for (directory_iterator dir_iter(pdbqt_folder); dir_iter != end_dir_iter; ++dir_iter)
	{
		if (!is_regular_file(dir_iter->status())) continue;
		const path p = dir_iter->path();
		if (p.extension().string() != ".pdbqt") continue;
		ids.push_back(new string(p.stem().string().substr(4)));
		if (ids.size() == milestone)
		{
			cout << milestone/1000 << "k\n";
			milestone += step;
		}
	}

	const size_t num_ids = ids.size();
	cout << "Sorting " << num_ids << " pdbqt files\n";
	ids.sort();

	ofstream out(argv[2]);
	for (size_t i = 0; i < num_ids; ++i)
	{
		out << ids[i] << '\n';
	}
*/
	cout << "Reading ids\n";
	const path pdbqt_folder = argv[1];
	ifstream in(pdbqt_folder / "ids");
	while (getline(in, line))
	{
		ids.push_back(line);
	}
	const size_t num_ids = ids.size();

	cout << "Checking and combining " << num_ids << " pdbqt files\n";
	const path out_folder = argv[2];
	for (size_t s = lexical_cast<size_t>(argv[3]); ; ++s)
	{
		cout << "Slice " << s << '\n';
		const size_t start = step * s; // Inclusive
		const size_t end = std::min(num_ids, step * (s + 1)); // Exclusive
		ofstream out(out_folder / (lexical_cast<string>(s) + ".pdbqt"));
		for (size_t i = start; i < end; ++i)
		{
			const string& id = ids[i];
			out << "HEADER    ZINC" << id << "                            06-APR-12                    \n";
			ifstream in(pdbqt_folder / ("ZINC" + id + ".pdbqt"));
			getline(in, line);
			if (!starts_with(line, remark)) throw logic_error(id); // cout << id << '\n';
			bool tor = false;
			while (getline(in, line))
			{
				if (starts_with(line, remark)) continue;
				out << line << '\n';
				if (starts_with(line, torsdof)) tor = true;
			}
			if (!tor) throw logic_error(id); // cout << id << '\n';
		}
		if (end == num_ids) break;
	}

	return 0;
}
