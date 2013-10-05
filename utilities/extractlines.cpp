#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>

using std::cout;
using std::vector;
using std::string;
using boost::filesystem::path;
using boost::filesystem::ifstream;

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

size_t binary(const vector<string>& ids, const string& id)
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
	return s;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "extractlines 16_prop.xls 16_p0.0.0.csv\n";
		return 0;
	}

	vector<string> lines;
	lines.reserve(1000);
	string line;
	line.reserve(200);

	// Read 16_p0.0.0.csv
	ifstream csv(argv[2]);
	while (getline(csv, line))
	{
		lines.push_back(line);
	}
	csv.close();
	const size_t num_lines = lines.size();

	// Read 16_prop.xls
	ifstream xls(argv[1]);
	getline(xls, line); // Filter out header line.
	for (size_t i = 0; getline(xls, line) && (i < num_lines);)
	{
		if (starts_with(line, lines[i]))
		{
			cout << lines[i];
			size_t s = 13, e;
			for (size_t j = 0; j < 9; ++j) // 9 properties, i.e. MWT,LogP,Desolv_apolar,Desolv_polar,HBD,HBA,tPSA,Charge,NRB
			{
				e = line.find_first_of('\t', s + 1);
				cout << ',' << line.substr(s, e - s);
				s = e + 1;
			}
			cout << ',' << line.substr(s) << '\n';
			++i;
		}
	}
	xls.close();

	return 0;
}

