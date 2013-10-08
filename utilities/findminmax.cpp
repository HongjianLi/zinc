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

	double mwt_lb = 600, mwt_ub = 0, lgp_lb = 10, lgp_ub = -5, ads_lb = 30, ads_ub = -20, pds_lb = 10, pds_ub = -500, psa_lb = 300, psa_ub = 0;
	size_t hbd_lb = 20, hbd_ub = 0, hba_lb = 18, hba_ub = 0, nrb_lb = 34, nrb_ub = 0;
	int chg_lb = 5, chg_ub = -5;
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
		const double lgp = lexical_cast<double>(line.substr(t3 + 1, t4 - t3 - 1));
		const double ads = lexical_cast<double>(line.substr(t4 + 1, t5 - t4 - 1));
		const double pds = lexical_cast<double>(line.substr(t5 + 1, t6 - t5 - 1));
		const size_t hbd = lexical_cast<size_t>(line.substr(t6 + 1, t7 - t6 - 1));
		const size_t hba = lexical_cast<size_t>(line.substr(t7 + 1, t8 - t7 - 1));
		const double psa = lexical_cast<double>(line.substr(t8 + 1, t9 - t8 - 1));
		const int chg = lexical_cast<int>(line.substr(t9 + 1, t10 - t9 - 1));
		const size_t nrb = lexical_cast<size_t>(line.substr(t10 + 1, t11 - t10 - 1));
		if (mwt_lb > mwt) mwt_lb = mwt;
		if (mwt_ub < mwt) mwt_ub = mwt;
		if (lgp_lb > lgp) lgp_lb = lgp;
		if (lgp_ub < lgp) lgp_ub = lgp;
		if (ads_lb > ads) ads_lb = ads;
		if (ads_ub < ads) ads_ub = ads;
		if (pds_lb > pds) pds_lb = pds;
		if (pds_ub < pds) pds_ub = pds;
		if (hbd_lb > hbd) hbd_lb = hbd;
		if (hbd_ub < hbd) hbd_ub = hbd;
		if (hba_lb > hba) hba_lb = hba;
		if (hba_ub < hba) hba_ub = hba;
		if (psa_lb > psa) psa_lb = psa;
		if (psa_ub < psa) psa_ub = psa;
		if (chg_lb > chg) chg_lb = chg;
		if (chg_ub < chg) chg_ub = chg;
		if (nrb_lb > nrb) nrb_lb = nrb;
		if (nrb_ub < nrb) nrb_ub = nrb;
	}
	in.close();
	cout << "mwt," << mwt_lb << ',' << mwt_ub << '\n' << "lgp," << lgp_lb << ',' << lgp_ub << '\n' << "ads," << ads_lb << ',' << ads_ub << '\n' << "pds," << pds_lb << ',' << pds_ub << '\n' << "hbd," << hbd_lb << ',' << hbd_ub << '\n' << "hba," << hba_lb << ',' << hba_ub << '\n' << "psa," << psa_lb << ',' << psa_ub << '\n' << "chg," << chg_lb << ',' << chg_ub << '\n' << "nrb," << nrb_lb << ',' << nrb_ub << '\n';
	return 0;
}
