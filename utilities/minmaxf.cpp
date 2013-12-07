#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	float vmin = numeric_limits<float>::max();
	float vmax = numeric_limits<float>::min();
	for (string line; getline(cin, line);)
	{
		const float v = stof(line);
		vmin = min<float>(vmin, v);
		vmax = max<float>(vmax, v);
	}
	cout << vmin << '\n' << vmax << '\n';
}