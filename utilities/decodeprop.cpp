#include <iostream>
#include <fstream>
#include <boost/timer/timer.hpp>

using std::cout;
using std::ifstream;
using boost::timer::auto_cpu_timer;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "decodeprop 16_prop.bin\n";
		return 0;
	}

	auto_cpu_timer r;
	ifstream bin(argv[1]);
	for (size_t i = 0; i < 12171187; ++i)
	{
		uint32_t id;
		float mwt, lgp, ads, pds;
		int16_t hbd, hba, psa, chg, nrb;
		bin.read((char*)&id, sizeof(id))
		   .read((char*)&mwt, sizeof(mwt))
		   .read((char*)&lgp, sizeof(lgp))
		   .read((char*)&ads, sizeof(ads))
		   .read((char*)&pds, sizeof(pds))
		   .read((char*)&hbd, sizeof(hbd))
		   .read((char*)&hba, sizeof(hba))
		   .read((char*)&psa, sizeof(psa))
		   .read((char*)&chg, sizeof(chg))
		   .read((char*)&nrb, sizeof(nrb));
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
