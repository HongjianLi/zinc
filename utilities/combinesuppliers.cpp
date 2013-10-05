#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

using std::cout;
using std::string;
using std::vector;
using boost::filesystem::path;
using boost::filesystem::ifstream;
using boost::filesystem::ofstream;
using boost::filesystem::directory_iterator;

class record
{
public:
	string id;
	vector<string> suppliers;
	explicit record(const string& id) : id(id) {}

	record(const record&) = default;
	record(record&&) = default;
	record& operator=(const record&) = default;
	record& operator=(record&&) = default;
};

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
		cout << "combinesuppliers 16_id.tsv suppliers_folder 16_sup.tsv\n";
		return 0;
	}

	vector<record> records;
	records.reserve(12171187);
	string line;

	// Load ids.
	ifstream log(argv[1]);
	getline(log, line); // Filter out header line.
	while (getline(log, line))
	{
		records.push_back(record(line));
	}
	const size_t num_records = records.size();
	cout << "Found " << num_records << " records\n";

	vector<string> suppliers;
	const path suppliers_folder = argv[2];
	const directory_iterator end_dir_iter;
	for (directory_iterator dir_iter(suppliers_folder); dir_iter != end_dir_iter; ++dir_iter)
	{
		if (!is_regular_file(dir_iter->status())) continue;
		const path p = dir_iter->path();
		const string filename = p.filename().string();
		const string supplier = filename.substr(0, filename.size() - 9);
		suppliers.push_back(supplier);
	}
	std::sort(suppliers.begin(), suppliers.end());
	for (const auto& supplier : suppliers)
	{
		cout << supplier << '\n';
		ifstream prop(suppliers_folder / (supplier + "_prop.xls"));
		getline(prop, line); // Filter out header line.
		while (getline(prop, line))
		{
			const string id = line.substr(4, 8);
			auto& r = records[binary(records, id)];
			if ((r.id == id) && (r.suppliers.empty() || r.suppliers.back() != supplier)) // supplier_prop.xls may contain two entries for one single ZINC_ID, e.g. chembl12_prop.xls contains two ZINC00000017, for different pH values.
			{
				r.suppliers.push_back(supplier);
			}
		}
	}

	// Output combined tsv.
	cout << "Writing combined tsv\n";
	ofstream out(argv[3]);
	out << "ZINC_ID\tSuppliers\n";
	for (const auto& r : records)
	{
		out << r.id << '\t' << r.suppliers.size();
		for (const auto& supplier : r.suppliers) out << '\t' << supplier;
		out << '\n';
	}

	return 0;
}
