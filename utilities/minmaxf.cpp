#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	size_t vmin = numeric_limits<float>::max();
	size_t vmax = 0;
	for (string line; getline(cin, line);)
	{
		const size_t v = stoul(line);
		vmin = min<float>(vmin, v);
		vmax = max<float>(vmax, v);
	}
	cout << vmin << '\n' << vmax << '\n';
}