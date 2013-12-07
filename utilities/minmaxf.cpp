#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	float vmin = numeric_limits<float>::max();
	float vmax = 0;
	for (string line; getline(cin, line);)
	{
		const float v = stoul(line);
		vmin = min<float>(vmin, v);
		vmax = max<float>(vmax, v);
	}
	cout << vmin << '\n' << vmax << '\n';
}