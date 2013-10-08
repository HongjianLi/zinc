#include <iostream>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

using std::cout;
using std::string;
using std::ifstream;
using boost::lexical_cast;
using boost::timer::auto_cpu_timer;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "castprop 16_prop.tsv\n";
		return 0;
	}

	auto_cpu_timer r;
	string line;
	line.reserve(200);
	ifstream tsv(argv[1]);
	getline(tsv, line); // Filter out header
	while (getline(tsv, line))
	{
		const auto t1 = 8; // id\tmwt
		const auto t2 = line.find_first_of('\t', t1 + 3); // mwt\tlgp
		const auto t3 = line.find_first_of('\t', t2 + 5); // lgp\tads
		const auto t4 = line.find_first_of('\t', t3 + 2); // ads\tpds
		const auto t5 = line.find_first_of('\t', t4 + 2); // pds\thbd
		const auto t6 = line.find_first_of('\t', t5 + 2); // hbd\thba
		const auto t7 = line.find_first_of('\t', t6 + 2); // hba\tpsa
		const auto t8 = line.find_first_of('\t', t7 + 2); // psa\tchg
		const auto t9 = line.find_first_of('\t', t8 + 2); // chg\tnrb
		const auto t10 = line.find_first_of('\t', t9 + 2); // nrb\tsmiles
		const auto id = lexical_cast<uint32_t>(line.substr(0, t1));
		const auto mwt = lexical_cast<float>(line.substr(t1 + 1, t2 - t1 - 1));
		const auto lgp = lexical_cast<float>(line.substr(t2 + 1, t3 - t2 - 1));
		const auto ads = lexical_cast<float>(line.substr(t3 + 1, t4 - t3 - 1));
		const auto pds = lexical_cast<float>(line.substr(t4 + 1, t5 - t4 - 1));
		const auto hbd = lexical_cast<int16_t>(line.substr(t5 + 1, t6 - t5 - 1));
		const auto hba = lexical_cast<int16_t>(line.substr(t6 + 1, t7 - t6 - 1));
		const auto psa = lexical_cast<int16_t>(line.substr(t7 + 1, t8 - t7 - 1));
		const auto chg = lexical_cast<int16_t>(line.substr(t8 + 1, t9 - t8 - 1));
		const auto nrb = lexical_cast<int16_t>(line.substr(t9 + 1, t10 - t9 - 1));
/*
		cout << id << '\t'
		     << mwt << '\t'
		     << lgp << '\t'
		     << ads << '\t'
		     << pds << '\t'
		     << hbd << '\t'
		     << hba << '\t'
		     << psa << '\t'
		     << chg << '\t'
		     << nrb << '\n';
*/
	}
}
