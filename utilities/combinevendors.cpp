#include <iostream>
#include <string>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

using std::cout;
using std::cerr;
using std::string;
using std::vector;
using boost::ptr_vector;
using boost::lexical_cast;
using boost::filesystem::path;
using boost::filesystem::ifstream;
using boost::filesystem::ofstream;
using boost::filesystem::directory_iterator;

class record
{
public:
	string line;
	string id;
	float fe;
	vector<string> vendors;
	explicit record(const string& line) : line(line)
	{
		const size_t comma = line.find(',', 1);
		id = line.substr(comma + 1, 8);
		fe = lexical_cast<float>(line.substr(comma + 12, line.find(',', comma + 18) - comma - 12));
	}
	record(const record&) = default;
	record(record&&) = default;
	record& operator=(const record&) = default;
	record& operator=(record&&) = default;
};

size_t binary(const ptr_vector<record>& records, const string& id)
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
		cout << "combinevendors log.csv vendors_folder out.csv\n";
		return 0;
	}

	ptr_vector<record> records(7220836);
	string line, header;

	// Scan log.csv for the first time.
	ifstream log(argv[1]);
	getline(log, header); // Save header line.
	while (getline(log, line))
	{
		records.push_back(new record(line));
	}
	const size_t num_records = records.size();
	cout << "Sorting " << num_records << " records in the ascending order of ID\n";
	std::sort(records.begin(), records.end(), [&] (const record& a, const record& b) -> bool { return a.id < b.id; });

	const path vendors_folder = argv[2];
	const directory_iterator end_dir_iter;
	for (directory_iterator dir_iter(vendors_folder); dir_iter != end_dir_iter; ++dir_iter)
	{
		if (!is_regular_file(dir_iter->status())) continue;
		const path p = dir_iter->path();
		const string filename = p.filename().string();
		const string vendor = filename.substr(0, filename.size() - 9);
		cout << "Processing " << vendor << '\n';
		ifstream prop(p);
		getline(prop, line); // Filter out header line.
		size_t t, c;
		for (t = 0, c = 0; getline(prop, line); ++t)
		{
			const string id = line.substr(4, 8);
			const size_t s = binary(records, id);
			if (records[s].id == id)
			{
				records[s].vendors.push_back(vendor);
			}
			else
			{
				const auto mwt = lexical_cast<float>(line.substr(13, line.find('\t', 14) - 13));
				if (mwt > 350) ++c;
			}
		}
		cout << c << " records with mwt > 350 out of " << t << " records are in prop but not in log\n";
	}

	cout << "Sorting records in the ascending order of energy\n";
	std::sort(records.begin(), records.end(), [&] (const record& a, const record& b) -> bool { return a.fe < b.fe; });

	// Output combined csv.
	cout << "Writing combined csv\n";
	ofstream out(argv[3]);
	out << header << ",Vendors\n";
	for (const auto& r : records)
	{
		out << r.line << ',' << r.vendors.size();
		for (const auto& v : r.vendors) out << ',' << v;
		out << '\n';
	}

	return 0;
}
