#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[])
{
	using std::cout;
	using std::ifstream;
	using std::string;
	using boost::lexical_cast;

	if (argc == 1)
	{
		std::cout << "countligands 16_prop_slice_ss.xls\n";
		return 0;
	}

	const float mwt_lb = 400;
	const float mwt_ub = 500;
	const float lgp_lb = 0;
	const float lgp_ub = 5;
	const int nrb_lb = 2;
	const int nrb_ub = 8;
	const int hbd_lb = 2;
	const int hbd_ub = 5;
	const int hba_lb = 2;
	const int hba_ub = 10;
	const int chg_lb = 0;
	const int chg_ub = 0;
	const float ads_lb = 0;
	const float ads_ub = 12;
	const float pds_lb = -50;
	const float pds_ub = 0;
	const float psa_lb = 20;
	const float psa_ub = 100;

	// Allocate host memory
	cout << "Allocating host memory" << std::endl;
	const size_t max_size = 4 * 12171187; // 46.5MB
	float* h_mwt = (float*)malloc(max_size);
	float* h_lgp = (float*)malloc(max_size);
	float* h_nrb = (float*)malloc(max_size);
	float* h_hbd = (float*)malloc(max_size);
	float* h_hba = (float*)malloc(max_size);
	float* h_chg = (float*)malloc(max_size);
	float* h_ads = (float*)malloc(max_size);
	float* h_pds = (float*)malloc(max_size);
	float* h_psa = (float*)malloc(max_size);

	// Read 16_prop_slice_ss.xls
	cout << "Reading prop.xls" << std::endl;
	size_t num_ligands = 0;
	string line;
	line.reserve(200);
	ifstream prop;
	prop.open(argv[1]);
	getline(prop, line); // Filter out header line
	while (getline(prop, line))
	{
		const size_t t2 = line.find_first_of('\t', 10);
		const size_t t3 = line.find_first_of('\t', t2 + 2);
		const size_t t4 = line.find_first_of('\t', t3 + 2);
		const size_t t5 = line.find_first_of('\t', t4 + 2);
		const size_t t6 = line.find_first_of('\t', t5 + 2);
		const size_t t7 = line.find_first_of('\t', t6 + 2);
		const size_t t8 = line.find_first_of('\t', t7 + 2);
		const size_t t9 = line.find_first_of('\t', t8 + 2);
		const size_t t10 = line.find_first_of('\t', t9 + 2);
		const size_t t11 = line.find_first_of('\t', t10 + 2);
		const float mwt = lexical_cast<float>(line.substr(t2 + 1, t3 - t2 - 1));
		const float lgp = lexical_cast<float>(line.substr(t3 + 1, t4 - t3 - 1));
		const float ads = lexical_cast<float>(line.substr(t4 + 1, t5 - t4 - 1));
		const float pds = lexical_cast<float>(line.substr(t5 + 1, t6 - t5 - 1));
		const int hbd = lexical_cast<int>(line.substr(t6 + 1, t7 - t6 - 1));
		const int hba = lexical_cast<int>(line.substr(t7 + 1, t8 - t7 - 1));
		const float psa = lexical_cast<float>(line.substr(t8 + 1, t9 - t8 - 1));
		const int chg = lexical_cast<int>(line.substr(t9 + 1, t10 - t9 - 1));
		const int nrb = lexical_cast<int>(line.substr(t10 + 1, t11 - t10 - 1));
		h_mwt[num_ligands] = mwt;
		h_lgp[num_ligands] = lgp;
		h_nrb[num_ligands] = nrb;
		h_hbd[num_ligands] = hbd;
		h_hba[num_ligands] = hba;
		h_chg[num_ligands] = chg;
		h_ads[num_ligands] = ads;
		h_pds[num_ligands] = pds;
		h_psa[num_ligands] = psa;
		++num_ligands;
	}
	cout << "Found " << num_ligands << " ligands" << std::endl;

	// Compute on CPU side
	int count = 0;
	for (size_t i = 0; i < num_ligands; ++i)
	{
		const float mwt = h_mwt[i];
		const float lgp = h_lgp[i];
		const int nrb = h_nrb[i];
		const int hbd = h_hbd[i];
		const int hba = h_hba[i];
		const int chg = h_chg[i];
		const float ads = h_ads[i];
		const float pds = h_pds[i];
		const float psa = h_psa[i];
		if ((mwt_lb <= mwt) && (mwt <= mwt_ub) && (lgp_lb <= lgp) && (lgp <= lgp_ub) && (nrb_lb <= nrb) && (nrb <= nrb_ub) && (hbd_lb <= hbd) && (hbd <= hbd_ub) && (hba_lb <= hba) && (hba <= hba_ub) && (chg_lb <= chg) && (chg <= chg_ub) && (ads_lb <= ads) && (ads <= ads_ub) && (pds_lb <= pds) && (pds <= pds_ub) && (psa_lb <= psa) && (psa <= psa_ub)) ++count;
	}
	cout << "CPU = " << count << std::endl;

	// Free resources
	free(h_mwt);
	free(h_lgp);
	free(h_nrb);
	free(h_hbd);
	free(h_hba);
	free(h_chg);
	free(h_ads);
	free(h_pds);
	free(h_psa);

	return 0;
}
