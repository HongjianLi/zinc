#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	vector<double> s;
	size_t n = 0;
	for (string line; getline(cin, line); ++n)
	{
		size_t sz = 1;
		size_t c0 = 0;
		for (size_t c1; (c1 = line.find(',', c0)) != string::npos; c0 = c1 + 1, ++sz)
		{
			if (sz > s.size()) s.resize(sz);
			s[sz - 1] += stod(line.substr(c0, c1 - c0));
		}
		if (sz > s.size()) s.resize(sz);
		s[sz - 1] += stod(line.substr(c0));
	}
	const float q = 1.0 / n;
	for (auto& d : s) d *= q;
	cout.setf(ios::fixed, ios::floatfield);
	cout << setprecision(3) << s[0];
	for (size_t i = 1; i < s.size(); ++i)
	{
		cout << ',' << s[i];
	}
	cout << endl;
}
