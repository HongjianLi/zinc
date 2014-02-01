#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string trim(string&& s)
{
	return s.substr(s.find_first_not_of(' '));
}

bool output(const string& id, const bool nid, string& prop, string& purch, float& mwt_lb, float& mwt_ub, float& lgp_lb, float& lgp_ub, float& ads_lb, float& ads_ub, float& pds_lb, float& pds_ub, int16_t& hbd_lb, int16_t& hbd_ub, int16_t& hba_lb, int16_t& hba_ub, int16_t& psa_lb, int16_t& psa_ub, int16_t& chg_lb, int16_t& chg_ub, int16_t& nrb_lb, int16_t& nrb_ub, ifstream& ifsprop, ifstream& ifspurch, ifstream& ifslig, ofstream& ofsid, ofstream& ofshdr, ofstream& ofsproptsv, ofstream& ofspropbin, ofstream& ofslig)
{
	// Check if new property and purchasing information exists
	while (prop.substr(4, 8) < id && getline(ifsprop, prop));
	while (purch.substr(4, 8) < id && getline(ifspurch, purch));
	const bool exist = prop.substr(4, 8) == id && purch.substr(4, 8) == id;

	// Skip ligands without properties or purchasing information.
	if (!exist && nid) return false;

	// Output id and hdr
	ofsid << id << '\n';
	const size_t p = ofslig.tellp();
	ofshdr.write((char*)&p, sizeof(p));

	// If new property and purchasing information exists, output it
	float mwt, lgp, ads, pds;
	int16_t hbd, hba, psa, chg, nrb;
	ostringstream proptsv, remarks;
	string line;
	if (exist)
	{
		// Parse property information
		const size_t t1 = prop.find('\t',     14); // mwt\tlgp
		const size_t t2 = prop.find('\t', t1 + 5); // lgp\tads
		const size_t t3 = prop.find('\t', t2 + 2); // ads\tpds
		const size_t t4 = prop.find('\t', t3 + 2); // pds\thbd
		const size_t t5 = prop.find('\t', t4 + 2); // hbd\thba
		const size_t t6 = prop.find('\t', t5 + 2); // hba\tpsa
		const size_t t7 = prop.find('\t', t6 + 2); // psa\tchg
		const size_t t8 = prop.find('\t', t7 + 2); // chg\tnrb
		const size_t t9 = prop.find('\t', t8 + 2); // nrb\tsmiles
		proptsv << prop.substr(13, t9 - 13) << '\n';
		mwt = stof(prop.substr(13, t1 - 13));
		lgp = stof(prop.substr(t1 + 1, t2 - t1 - 1));
		ads = stof(prop.substr(t2 + 1, t3 - t2 - 1));
		pds = stof(prop.substr(t3 + 1, t4 - t3 - 1));
		hbd = stoul(prop.substr(t4 + 1, t5 - t4 - 1));
		hba = stoul(prop.substr(t5 + 1, t6 - t5 - 1));
		psa = stoul(prop.substr(t6 + 1, t7 - t6 - 1));
		chg = stoi(prop.substr(t7 + 1, t8 - t7 - 1));
		nrb = stoul(prop.substr(t8 + 1, t9 - t8 - 1));
		remarks
			<< "REMARK     " << id
			<< ' ' << setw(8) << mwt
			<< ' ' << setw(8) << lgp
			<< ' ' << setw(8) << ads
			<< ' ' << setw(8) << pds
			<< ' ' << setw(3) << hbd
			<< ' ' << setw(3) << hba
			<< ' ' << setw(3) << psa
			<< ' ' << setw(3) << chg
			<< ' ' << setw(3) << nrb
			<< "    \n";

		const string smiles = prop.substr(t9 + 1);
		remarks << "REMARK     " << smiles << '\n';

		// Parse purchasing information
		vector<string> suppliers;
		do
		{
			const auto& s = purch.substr(13, purch.find('\t', 14) - 13);
			if (find(suppliers.cbegin(), suppliers.cend(), s) == suppliers.cend()) // Remove duplicates
			{
				suppliers.push_back(s); // supplier\tsuppliercode
			}
		} while (getline(ifspurch, purch) && purch.substr(4, 8) == id);
		sort(suppliers.begin(), suppliers.end());
		remarks << "REMARK     " << suppliers.size();
		for (const auto& s : suppliers) remarks << " | " << s;
		remarks << '\n';

		// Filter out the three original REMARK lines
		if (!nid)
		{
			getline(ifslig, line);
			getline(ifslig, line);
			getline(ifslig, line);
		}
	}
	// Otherwise output existing property and purchasing information
	else
	{
		// Parse property REMARK line
		getline(ifslig, line);
		if (line.substr(11, 8) != id) cerr << line.substr(11, 8) << " == line.substr(11, 8) != id == " << id << endl;
		const string smwt = trim(line.substr(20, 8));
		const string slgp = trim(line.substr(29, 8));
		const string sads = trim(line.substr(38, 8));
		const string spds = trim(line.substr(47, 8));
		const string shbd = trim(line.substr(56, 3));
		const string shba = trim(line.substr(60, 3));
		const string spsa = trim(line.substr(64, 3));
		const string schg = trim(line.substr(68, 3));
		const string snrb = trim(line.substr(72, 3));
		proptsv
			<< smwt << '\t'
			<< slgp << '\t'
			<< sads << '\t'
			<< spds << '\t'
			<< shbd << '\t'
			<< shba << '\t'
			<< spsa << '\t'
			<< schg << '\t'
			<< snrb << '\n';
		mwt = stof(smwt);
		lgp = stof(slgp);
		ads = stof(sads);
		pds = stof(spds);
		hbd = stoul(shbd);
		hba = stoul(shba);
		psa = stoul(spsa);
		chg = stoi(schg);
		nrb = stoul(snrb);
		remarks << line << '\n';

		// Parse smiles REMARK line
		getline(ifslig, line);
		remarks << line << '\n';

		// Parse supplier REMARK line
		getline(ifslig, line);
		remarks << line << '\n';
	}
	// Output proptsv, propbin and lig remark lines
	ofsproptsv << proptsv.str();
	ofspropbin
		.write((char*)&mwt, sizeof(mwt))
		.write((char*)&lgp, sizeof(lgp))
		.write((char*)&ads, sizeof(ads))
		.write((char*)&pds, sizeof(pds))
		.write((char*)&hbd, sizeof(hbd))
		.write((char*)&hba, sizeof(hba))
		.write((char*)&psa, sizeof(psa))
		.write((char*)&chg, sizeof(chg))
		.write((char*)&nrb, sizeof(nrb));
	ofslig << remarks.str();
	// Update min & max
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
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 13)
	{
		cout << "updatepdbqt ~/istar/idock/16_id.csv 16_id_new.csv 16_prop.xls 16_purch.xls ~/istar/idock/16_lig.pdbqt pdbqt_folder 16_id.csv 16_hdr.bin 16_prop.tsv 16_prop.bin 16_lig.pdbqt minmax.csv\n";
		return 0;
	}

	const auto prefix = string(argv[6]) + "/";
	const auto suffix = ".pdbqt";
	const auto mid = "99999999";
	string line, oid, nid, prop, purch;
	ifstream ifsoid(argv[1]);
	ifstream ifsnid(argv[2]);
	ifstream ifsprop(argv[3]);
	ifstream ifspurch(argv[4]);
	ifstream ifslig(argv[5]);
	ofstream ofsid(argv[7]);
	ofstream ofshdr(argv[8]);
	ofstream ofsproptsv(argv[9]);
	ofstream ofspropbin(argv[10]);
	ofstream ofslig(argv[11]);
	getline(ifsoid, oid); // Initialize oid
	if (!getline(ifsnid, nid)) nid = mid; // Initialize nid. Set nid = mid in case 16_id_new.csv is empty
	getline(ifsprop,  prop);  // Filter out header line
	ofsproptsv << prop.substr(8, 59) << '\n'; // For prop.R, filter out the first ZINC_ID column and the last SMILES column
	getline(ifsprop,  prop);  // Initialize prop
	getline(ifspurch, purch); // Filter out header line
	getline(ifspurch, purch); // Initialize purch
	float mwt_lb = 600, mwt_ub = 0, lgp_lb = 10, lgp_ub = -5, ads_lb = 30, ads_ub = -20, pds_lb = 10, pds_ub = -500;
	int16_t hbd_lb = 20, hbd_ub = 0, hba_lb = 18, hba_ub = 0, psa_lb = 300, psa_ub = 0, chg_lb = 5, chg_ub = -5, nrb_lb = 34, nrb_ub = 0;
	size_t num_incomplete_ligands = 0;
	while (oid != mid || nid != mid)
	{
		for (; oid < nid; oid = getline(ifsoid, oid) ? oid : mid)
		{
			output(oid, false, prop, purch, mwt_lb, mwt_ub, lgp_lb, lgp_ub, ads_lb, ads_ub, pds_lb, pds_ub, hbd_lb, hbd_ub, hba_lb, hba_ub, psa_lb, psa_ub, chg_lb, chg_ub, nrb_lb, nrb_ub, ifsprop, ifspurch, ifslig, ofsid, ofshdr, ofsproptsv, ofspropbin, ofslig);
			while (getline(ifslig, line))
			{
				ofslig << line << '\n';
				if (line[0] == 'T') break;
			}
		}
		for (; nid < oid; nid = getline(ifsnid, nid) ? nid : mid)
		{
			if (!output(nid, true, prop, purch, mwt_lb, mwt_ub, lgp_lb, lgp_ub, ads_lb, ads_ub, pds_lb, pds_ub, hbd_lb, hbd_ub, hba_lb, hba_ub, psa_lb, psa_ub, chg_lb, chg_ub, nrb_lb, nrb_ub, ifsprop, ifspurch, ifslig, ofsid, ofshdr, ofsproptsv, ofspropbin, ofslig))
			{
				//cerr << nid << " no prop or purch\n";
				++num_incomplete_ligands;
				continue;
			}
			ifstream pdbqt(prefix + nid + suffix);
			while (getline(pdbqt, line) && line.size() != 4); // ROOT
			do { ofslig << line << '\n'; } while (getline(pdbqt, line));
		}
	}
	cout << num_incomplete_ligands << " ligands no prop or purch" << endl;
	ofstream minmax(argv[12]);
	minmax
	<< "mwt_lb," << mwt_lb << '\n'
	<< "mwt_ub," << mwt_ub << '\n'
	<< "lgp_lb," << lgp_lb << '\n'
	<< "lgp_ub," << lgp_ub << '\n'
	<< "ads_lb," << ads_lb << '\n'
	<< "ads_ub," << ads_ub << '\n'
	<< "pds_lb," << pds_lb << '\n'
	<< "pds_ub," << pds_ub << '\n'
	<< "hbd_lb," << hbd_lb << '\n'
	<< "hbd_ub," << hbd_ub << '\n'
	<< "hba_lb," << hba_lb << '\n'
	<< "hba_ub," << hba_ub << '\n'
	<< "psa_lb," << psa_lb << '\n'
	<< "psa_ub," << psa_ub << '\n'
	<< "chg_lb," << chg_lb << '\n'
	<< "chg_ub," << chg_ub << '\n'
	<< "nrb_lb," << nrb_lb << '\n'
	<< "nrb_ub," << nrb_ub << '\n';
}
