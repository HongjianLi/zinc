#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using boost::lexical_cast;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "insertprop 16_lig.pdbqt 16_prop.tsv\n";
		return 0;
	}

	cout.setf(ios::fixed, ios::floatfield);
	cout << setprecision(3);
	string line;
	ifstream lig(argv[1]);
	ifstream prop(argv[2]);
	while (getline(lig, line))
	{
		if (line[0] == 'H')
		{
			cout << "REMARK     " << line.substr(14, 8);
			getline(prop, line);
			const auto t1 = line.find_first_of('\t',      3); // mwt\tlgp
			const auto t2 = line.find_first_of('\t', t1 + 5); // lgp\tads
			const auto t3 = line.find_first_of('\t', t2 + 2); // ads\tpds
			const auto t4 = line.find_first_of('\t', t3 + 2); // pds\thbd
			const auto t5 = line.find_first_of('\t', t4 + 2); // hbd\thba
			const auto t6 = line.find_first_of('\t', t5 + 2); // hba\tpsa
			const auto t7 = line.find_first_of('\t', t6 + 2); // psa\tchg
			const auto t8 = line.find_first_of('\t', t7 + 2); // chg\tnrb
			const auto mwt = lexical_cast<float>(line.substr(0, t1));
			const auto lgp = lexical_cast<float>(line.substr(t1 + 1, t2 - t1 - 1));
			const auto ads = lexical_cast<float>(line.substr(t2 + 1, t3 - t2 - 1));
			const auto pds = lexical_cast<float>(line.substr(t3 + 1, t4 - t3 - 1));
			const auto hbd = lexical_cast<uint32_t>(line.substr(t4 + 1, t5 - t4 - 1));
			const auto hba = lexical_cast<uint32_t>(line.substr(t5 + 1, t6 - t5 - 1));
			const auto psa = lexical_cast<uint32_t>(line.substr(t6 + 1, t7 - t6 - 1));
			const auto chg = lexical_cast<int32_t>(line.substr(t7 + 1, t8 - t7 - 1));
			const auto nrb = lexical_cast<uint32_t>(line.substr(t8 + 1));
			cout << ' ' << setw(8) << mwt
			     << ' ' << setw(8) << lgp
			     << ' ' << setw(8) << ads
			     << ' ' << setw(8) << pds
			     << ' ' << setw(3) << hbd
			     << ' ' << setw(3) << hba
			     << ' ' << setw(3) << psa
			     << ' ' << setw(3) << chg
			     << ' ' << setw(3) << nrb
			     << "    \n";
		}
		else
		{
			cout << line << '\n';
		}
	}
}
