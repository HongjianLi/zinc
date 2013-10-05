#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "minmax id.csv\n";
		return 0;
	}

	string line;
	size_t cmin, cmax;
	ifstream ifs(argv[1]);
	getline(ifs, line);
	cmin = cmax = stoul(line);
	while (getline(ifs, line))
	{
		const size_t v = stoul(line);
		cmin = min<size_t>(cmin, v);
		cmax = max<size_t>(cmax, v);
	}
	cout << cmin << '\n' << cmax << '\n';
}