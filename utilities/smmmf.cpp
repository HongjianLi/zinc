#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

void output(const vector<double>& v)
{
	cout << v[0];
	for (size_t i = 1; i < v.size(); ++i)
	{
		cout << ',' << v[i];
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	string line;
	if (!getline(cin, line)) return 0;

	// Determine the number of columns.
	const size_t w = count(line.begin(), line.end(), ',') + 1;
	vector<vector<double>> s(3);
	s[0].resize(w, 0);
	s[1].resize(w, numeric_limits<double>::max());
	s[2].resize(w, numeric_limits<double>::lowest());
	size_t n = 0;
	do
	{
		for (size_t i = 0, c0 = 0, c1; i < w; ++i, c0 = c1 + 1)
		{
			c1 = line.find(',', c0);
			if (c1 == string::npos) c1 = line.size();
			const auto v = stod(line.substr(c0, c1 - c0));
			s[0][i] += v;
			s[1][i] = min(s[1][i], v);
			s[2][i] = max(s[2][i], v);
		}
	} while (getline(cin, line) && ++n);

	// Compute column-wise mean.
	const auto q = 1.0 / n;
	vector<double> m(w);
	for (size_t i = 0; i < w; ++i)
	{
		m[i] = s[0][i] * q;
	}

	// Output sum, min, max
	cout.setf(ios::fixed, ios::floatfield);
	cout << setprecision(3);
	for (const auto& v : s)
	{
		output(v);
	}
	output(m);
}
