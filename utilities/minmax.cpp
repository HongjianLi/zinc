#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	size_t vmin = numeric_limits<size_t>::max();
	size_t vmax = numeric_limits<size_t>::min();
	for (string line; getline(cin, line);)
	{
		const size_t v = stoul(line);
		vmin = min<size_t>(vmin, v);
		vmax = max<size_t>(vmax, v);
	}
	cout << vmin << '\n' << vmax << '\n';
}