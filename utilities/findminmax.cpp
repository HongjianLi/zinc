#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/fstream.hpp>

using std::cout;
using std::string;
using boost::lexical_cast;
using boost::filesystem::ifstream;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "findminmax 16_prop.tsv\n";
		return 0;
	}

	double mwt_lb = 600, mwt_ub = 0, logp_lb = 10, logp_ub = -5, ad_lb = 30, ad_ub = -20, pd_lb = 10, pd_ub = -500, tpsa_lb = 300, tpsa_ub = 0;
	size_t hbd_lb = 20, hbd_ub = 0, hba_lb = 18, hba_ub = 0, nrb_lb = 34, nrb_ub = 0;
	int charge_lb = 5, charge_ub = -5;
	string line;
	line.reserve(200);
	ifstream in(argv[1]);
	getline(in, line); // Filter out header line
	while (getline(in, line))
	{
//		const size_t t2 = line.find_first_of('\t', 10);
		const size_t t2 = 8;
		const size_t t3 = line.find_first_of('\t', t2 + 2);
		const size_t t4 = line.find_first_of('\t', t3 + 2);
		const size_t t5 = line.find_first_of('\t', t4 + 2);
		const size_t t6 = line.find_first_of('\t', t5 + 2);
		const size_t t7 = line.find_first_of('\t', t6 + 2);
		const size_t t8 = line.find_first_of('\t', t7 + 2);
		const size_t t9 = line.find_first_of('\t', t8 + 2);
		const size_t t10 = line.find_first_of('\t', t9 + 2);
		const size_t t11 = line.find_first_of('\t', t10 + 2);
		const double mwt = lexical_cast<double>(line.substr(t2 + 1, t3 - t2 - 1));
		const double logp = lexical_cast<double>(line.substr(t3 + 1, t4 - t3 - 1));
		const double ad = lexical_cast<double>(line.substr(t4 + 1, t5 - t4 - 1));
		const double pd = lexical_cast<double>(line.substr(t5 + 1, t6 - t5 - 1));
		const size_t hbd = lexical_cast<size_t>(line.substr(t6 + 1, t7 - t6 - 1));
		const size_t hba = lexical_cast<size_t>(line.substr(t7 + 1, t8 - t7 - 1));
		const double tpsa = lexical_cast<double>(line.substr(t8 + 1, t9 - t8 - 1));
		const int charge = lexical_cast<int>(line.substr(t9 + 1, t10 - t9 - 1));
		const size_t nrb = lexical_cast<size_t>(line.substr(t10 + 1, t11 - t10 - 1));
		if (mwt_lb > mwt) mwt_lb = mwt;
		if (mwt_ub < mwt) mwt_ub = mwt;
		if (logp_lb > logp) logp_lb = logp;
		if (logp_ub < logp) logp_ub = logp;
		if (ad_lb > ad) ad_lb = ad;
		if (ad_ub < ad) ad_ub = ad;
		if (pd_lb > pd) pd_lb = pd;
		if (pd_ub < pd) pd_ub = pd;
		if (hbd_lb > hbd) hbd_lb = hbd;
		if (hbd_ub < hbd) hbd_ub = hbd;
		if (hba_lb > hba) hba_lb = hba;
		if (hba_ub < hba) hba_ub = hba;
		if (tpsa_lb > tpsa) tpsa_lb = tpsa;
		if (tpsa_ub < tpsa) tpsa_ub = tpsa;
		if (charge_lb > charge) charge_lb = charge;
		if (charge_ub < charge) charge_ub = charge;
		if (nrb_lb > nrb) nrb_lb = nrb;
		if (nrb_ub < nrb) nrb_ub = nrb;
	}
	in.close();
	cout << "mwt," << mwt_lb << ',' << mwt_ub << '\n' << "logp," << logp_lb << ',' << logp_ub << '\n' << "ad," << ad_lb << ',' << ad_ub << '\n' << "pd," << pd_lb << ',' << pd_ub << '\n' << "hbd," << hbd_lb << ',' << hbd_ub << '\n' << "hba," << hba_lb << ',' << hba_ub << '\n' << "tpsa," << tpsa_lb << ',' << tpsa_ub << '\n' << "charge," << charge_lb << ',' << charge_ub << '\n' << "nrb," << nrb_lb << ',' << nrb_ub << '\n';
	return 0;
}
