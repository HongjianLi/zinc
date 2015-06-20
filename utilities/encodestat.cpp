#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

int main()
{
	vector<string> tokens(21);
	for (string line; getline(cin, line);)
	{
		for (size_t comma0 = 0, index = 0; true;)
		{
			const size_t comma1 = line.find('\t', comma0 + 1);
			if (comma1 == string::npos)
			{
				tokens[index] = line.substr(comma0);
				break;
			}
			tokens[index++] = line.substr(comma0, comma1 - comma0);
			comma0 = comma1 + 1;
		}
		for (size_t i = 0; i < 20; ++i)
		{
			const int16_t val = stoi(tokens[i]);
			cout.write(reinterpret_cast<const char*>(&val), sizeof(val));
		}
		const float mwt = stof(tokens[20]);
		cout.write(reinterpret_cast<const char*>(&mwt), sizeof(mwt));
	}
}
