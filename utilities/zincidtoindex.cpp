#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "zincidtoindex 16_id.csv my_id.csv\n";
		return 0;
	}

	string id, line;
	ifstream rid(argv[1]);
	ifstream mid(argv[2]);
	for (size_t idx = 0; getline(mid, id);)
	{
		for (; getline(rid, line); ++idx)
		{
			if (line == id)
			{
				cout << idx++ << '\n';
				break;
			}
		}
	}
}
