#include <iostream>
#include <string>
#include <map>
#include <set>
#include <boost/filesystem/fstream.hpp>

using std::cout;
using std::string;
using std::map;
using std::set;
using boost::filesystem::path;
using boost::filesystem::ifstream;

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
	if (argc != 4)
	{
		cout << "extractpurch catalogs.tsv 16_id.csv 16_purch.xls\n";
		return 0;
	}

	string line;
	line.reserve(200);

//	cout << "Reading " << argv[1] << '\n';
	map<string, string> catalogs;
	ifstream catalogstsv(argv[1]);
	while (getline(catalogstsv, line))
	{
		const size_t sep = line.find('\t');
		catalogs[line.substr(sep + 1)] = line.substr(0, sep);
	}

//	cout << "Reading " << argv[3] << '\n';
	string id;
	ifstream idcsv(argv[2]);
	getline(idcsv, line); // Filter out header line.
	ifstream purchxls(argv[3]);
	getline(purchxls, line); // Filter out header line.
	getline(purchxls, line); // Buffer a line.
	while (getline(idcsv, id))
	{
		cout << id;
		set<string> vendors;
		for (string idp; line.size() && (idp = line.substr(4, 8)) <= id; getline(purchxls, line))
		{
			if (idp < id) continue;
			const string vendor = line.substr(13, line.find('\t', 14) - 13);
			if (!ends_with(vendor, "epleted)")) vendors.insert(catalogs[vendor]);
		}
		for (const auto& v : vendors) cout << '\t' << v;
		cout << '\n';
	}

	return 0;
}

