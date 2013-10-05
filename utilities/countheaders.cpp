#include <iostream>
#include <string>
#include <boost/filesystem/fstream.hpp>

using std::string;
using std::cout;
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

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "countheaders 16_lig.pdbqt 16_hdr.csv\n";
		return 0;
	}

	const size_t mask = (1 << 18) - 1;
	string line;
	line.reserve(80);
	size_t num_headers = 0, num_torsdofs = 0;
	ofstream out(argv[2]);
	out << "Offset\n"; // Header
	ifstream in(argv[1]);
	while (getline(in, line))
	{
		if (starts_with(line, "REMARK     ") && (line.size() == 79) && (line.find('|', 13) == string::npos))
		{
			++num_headers;
			const size_t pos = in.tellg();
			out << pos - 80 << '\n';
		}
		if (starts_with(line, "TORSDOF"))
		{
			++num_torsdofs;
			if (!(num_torsdofs & mask)) cout << num_torsdofs << '\n';
		}
	}
	cout << num_headers << " headers found\n";
	cout << num_torsdofs << " torsdofs found\n";
	return 0;
}
