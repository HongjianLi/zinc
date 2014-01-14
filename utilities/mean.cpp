#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[])
{
	size_t n = 0;
	double s = 0;
	for (string line; getline(cin, line);)
	{
		++n;
		s += stod(line);
	}
	cout.setf(ios::fixed, ios::floatfield);
	cout << setprecision(3) << s / n << endl;
}