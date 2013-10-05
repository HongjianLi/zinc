#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "alignfloat 2 < float.csv\n";
		return 0;
	}
	cout.setf(ios::fixed, ios::floatfield);
	cout << setprecision(stoi(argv[1]));
	for (string line; getline(cin, line);)
	{
		cout << stof(line) << endl;
	}
}
