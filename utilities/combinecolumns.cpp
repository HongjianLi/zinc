#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "combinecolumns file1 file2 ...\n";
		return 0;
	}

	vector<ifstream> ifstreams(argc - 1);
	for (size_t i = 0; i < argc - 1; ++i)
	{
		ifstreams[i].open(argv[i + 1]);
	}
	for (string line; getline(ifstreams.front(), line);)
	{
		cout << line;
		for (size_t i = 1; i < argc - 1; ++i)
		{
			getline(ifstreams[i], line);
			cout << ',' /*'\t'*/ << line;
		}
		cout << '\n';
	}
}
