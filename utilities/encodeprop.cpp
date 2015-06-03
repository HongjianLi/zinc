#include <iostream>
#include <fstream>
#include <vector>
//#include <cstdint>
using namespace std;

class property
{
public:
	float mwt, lgp, ads, pds;
	int hbd, hba, psa, chg, nrb;
};

int main()
{
	string line;
	vector<property> properties;
	vector<string> tokens(9);
	while (getline(cin, line))
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
		properties.push_back(property
		{
			stof(tokens[0]),
			stof(tokens[1]),
			stof(tokens[2]),
			stof(tokens[3]),
			stoi(tokens[4]),
			stoi(tokens[5]),
			stoi(tokens[6]),
			stoi(tokens[7]),
			stoi(tokens[8]),
		});
	}
	cout.write(reinterpret_cast<char*>(properties.data()), sizeof(property) * properties.size());
}
