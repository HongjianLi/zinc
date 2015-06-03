#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

class property
{
public:
	float mwt, lgp, ads, pds;
	int16_t hbd, hba, psa, chg, nrb;
};

int main()
{
	vector<string> tokens(9);
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
		property p
		{
			stof(tokens[0]),
			stof(tokens[1]),
			stof(tokens[2]),
			stof(tokens[3]),
			static_cast<int16_t>(stoi(tokens[4])),
			static_cast<int16_t>(stoi(tokens[5])),
			static_cast<int16_t>(stoi(tokens[6])),
			static_cast<int16_t>(stoi(tokens[7])),
			static_cast<int16_t>(stoi(tokens[8])),
		};
		cout.write(reinterpret_cast<char*>(&p), 26);
	}
}
