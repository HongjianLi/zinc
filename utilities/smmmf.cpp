#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	string line;
	if (!getline(cin, line)) return 0;

	// Determine the number of columns.
	const size_t w = count(line.begin(), line.end(), ',') + 1;
	vector<vector<double>> s(4);
	s[0].resize(w, 0);
	s[1].resize(w);
	s[2].resize(w, numeric_limits<double>::max());
	s[3].resize(w, numeric_limits<double>::lowest());
	size_t n = 0;
	do
	{
		for (size_t i = 0, c0 = 0, c1; i < w; ++i, c0 = c1 + 1)
		{
			c1 = line.find(',', c0);
			if (c1 == string::npos) c1 = line.size();
			const auto v = stod(line.substr(c0, c1 - c0));
			s[0][i] += v;
			s[2][i] = min(s[2][i], v);
			s[3][i] = max(s[3][i], v);
		}
	} while (getline(cin, line) && ++n);

	// Compute column-wise mean.
	const auto q = 1.0 / n;
	for (size_t i = 0;  i < w; ++i)
	{
		s[1][i] = s[0][i] * q;
	}

	// Output sum, mean, min, max
	cout.setf(ios::fixed, ios::floatfield);
	cout << setprecision(3);
	for (const auto& v : s)
	{
		cout << v[0];
		for (size_t i = 1; i < w; ++i)
		{
			cout << ',' << v[i];
		}
		cout << endl;
	}
}
