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
		float mwt, logp, ad, pd;
		int16_t hbd, hba, tpsa, charge, nrb;
		bin.read((char*)&id, sizeof(id))
		   .read((char*)&mwt, sizeof(mwt))
		   .read((char*)&logp, sizeof(logp))
		   .read((char*)&ad, sizeof(ad))
		   .read((char*)&pd, sizeof(pd))
		   .read((char*)&hbd, sizeof(hbd))
		   .read((char*)&hba, sizeof(hba))
		   .read((char*)&tpsa, sizeof(tpsa))
		   .read((char*)&charge, sizeof(charge))
		   .read((char*)&nrb, sizeof(nrb));
/*
		cout << id << '\t'
		     << mwt << '\t'
		     << logp << '\t'
		     << ad << '\t'
		     << pd << '\t'
		     << hbd << '\t'
		     << hba << '\t'
		     << tpsa << '\t'
		     << charge << '\t'
		     << nrb << '\n';
*/
	}
}
