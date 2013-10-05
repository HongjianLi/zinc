#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "overlaysubset 16_id_new.csv 16_prop_id_unique.tsv\n";
		return 0;
	}

	string sid, fid = "00000000";
	size_t num_outliers = 0;
	ifstream f(argv[2]);
	for (ifstream s(argv[1]); getline(s, sid);)
	{
		while (fid < sid && getline(f, fid));
		if (fid != sid)
		{
			//cout << sid << '\n';
			++num_outliers;
		}
	}
	cout << num_outliers << endl;
}
