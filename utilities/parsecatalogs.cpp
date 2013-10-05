#include <iostream>
#include <string>
#include <boost/filesystem/fstream.hpp>

using std::cout;
using std::string;
using boost::filesystem::ifstream;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "parsecatalogs catalogs.html\n";
		return 0;
	}

	string line;
	ifstream in(argv[1]);
	while (getline(in, line))
	{
		getline(in, line);
		// Parse line
		const size_t quote = line.find('"', 47);
		cout << line.substr(46, quote - 46) << ',' << line.substr(quote + 31, line.size() - quote - 33) << '\n';
		getline(in, line);
		getline(in, line);
		getline(in, line);
		getline(in, line);
		getline(in, line);
		getline(in, line);
		getline(in, line);
	}

	return 0;
}
