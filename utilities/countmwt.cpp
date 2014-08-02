#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <map>
using namespace std;

int main(int argc, char* argv[])
{
	const auto n = 14;;
	const array<string, n> ad =
	{
		"HD",
		"H ",
		"C ",
		"A ",
		"N ",
		"NA",
		"OA",
		"SA",
		"S ",
		"P ",
		"F ",
		"Cl",
		"Br",
		"I ",
	};
	const array<double, n> wt =
	{
		  1.008,
		  1.008,
		 12.01,
		 12.01,
		 14.01,
		 14.01,
		 16.00,
		 32.07,
		 32.07,
		 30.97,
		 19.00,
		 35.45,
		 79.90,
		126.90,
	};
	map<string, double> ad2wt;
	for (auto i = 0; i < n; ++i)
	{
		ad2wt[ad[i]] = wt[i];
	}
	size_t nha = 0;
	double mwt = 0;
	for (string line; getline(cin, line);)
	{
		const string record = line.substr(0, 6);
		if (record == "ATOM  " || record == "HETATM")
		{
			const string t = line.substr(77, 2);
			if (t != "HD" && t != "H ") ++nha;
			mwt += ad2wt.at(t);
		}
	}
	cout << nha << '\t' << mwt << endl;
}
