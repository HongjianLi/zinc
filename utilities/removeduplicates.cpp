#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "removeduplicates 16_id.csv 16_id_unique.csv\n";
		return 0;
	}

	string line;
	ifstream ifs(argv[1]);
	ofstream ofs(argv[2]);
	getline(ifs, line);
	ofs << line << '\n';
	size_t num_lines = 1, num_duplicates = 0;
	for (string prev = line; getline(ifs, line); prev = line)
	{
		if (line == prev) ++num_duplicates;
		else ofs << line << '\n';
		++num_lines;
	}
	cout << "lines" << '\t' << setw(10) << num_lines << '\n' << "dups" << '\t' << setw(10) << num_duplicates << '\n' << "unique" << '\t' << setw(10) << (num_lines - num_duplicates) << '\n';
}