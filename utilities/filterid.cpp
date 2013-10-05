#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "filterid old_16_id.csv new_16_id.csv\n";
		return 0;
	}

	string line;
	vector<string> ids;
//	ids.reserve(12171187); // Number of molecules in old_16_id.csv
	for (ifstream ifs(argv[1]); getline(ifs, line); ids.push_back(line));
	sort(ids.begin(), ids.end());
	const size_t l = ids.front().length();
	for (ifstream ifs(argv[2]); getline(ifs, line);)
	{
		if (!binary_search(ids.cbegin(), ids.cend(), line.substr(0, l))) cout << line << '\n';
	}
}
