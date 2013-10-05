#include <iostream>
#include <string>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/fstream.hpp>

using std::cout;
using std::string;
using boost::ptr_vector;
using boost::lexical_cast;
using boost::filesystem::ifstream;

class record
{
public:
	size_t index, pos, size;
	explicit record(const size_t index, const size_t pos, const size_t size) : index(index), pos(pos), size(size) {}
};

inline bool operator<(const record& a, const record& b)
{
	return a.size < b.size;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "checkheaders 16_headers.tsv ...\n";
		return 0;
	}

	ptr_vector<record> records(12171187);
	string line;
	line.reserve(80);
	ifstream in(argv[1]);
	getline(in, line);
	size_t p0 = lexical_cast<size_t>(line);
	for (size_t i = 0; getline(in, line); ++i)
	{
		const size_t p1 = lexical_cast<size_t>(line);
		records.push_back(new record(i, p0, p1 - p0));
		p0 = p1;
	}
	records.sort();
	const record& min = records.front();
	const record& max = records.back();
	cout << min.index << ',' << min.pos << ',' << min.size << '\n';
	cout << max.index << ',' << max.pos << ',' << max.size << '\n';
	return 0;
}
