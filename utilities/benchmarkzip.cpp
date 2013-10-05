#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/timer/timer.hpp>

int main(int argc, char* argv[])
{
	using std::cout;
	using std::string;
	using boost::lexical_cast;
	using namespace boost::filesystem;
	using namespace boost::iostreams;
	using namespace boost::timer;

	if (argc != 3)
	{
		cout << "boostzip stem.gz offset\n";
		return 0;
	}

	const path p = argv[1];
	const string ext = p.extension().string();
	string line;
/*
	const size_t max_size = 4 * 12171187; // 46.5MB
	float* h_mwt = (float*)malloc(max_size);
	float* h_logp = (float*)malloc(max_size);
	float* h_nrb = (float*)malloc(max_size);
	float* h_hbd = (float*)malloc(max_size);
	float* h_hba = (float*)malloc(max_size);
	float* h_charge = (float*)malloc(max_size);
	float* h_ad = (float*)malloc(max_size);
	float* h_pd = (float*)malloc(max_size);
	float* h_tpsa = (float*)malloc(max_size);

	size_t num_ligands = 0;
	auto_cpu_timer t;
*/

	ifstream in(p);
	filtering_istream fis;
	if (ext == ".gz") fis.push(gzip_decompressor()); else if (ext == ".bz2") fis.push(bzip2_decompressor());
	fis.push(in);
	in.seekg(lexical_cast<size_t>(argv[2]));
	for (size_t i = 0; i < 1; ++i)
	{
		getline(fis, line);
		cout << line << '\n';
/*
		const size_t t1 = line.find_first_of('\t', 3);
		const size_t t2 = line.find_first_of('\t', t1 + 5);
		const size_t t3 = line.find_first_of('\t', t2 + 2);
		const size_t t4 = line.find_first_of('\t', t3 + 2);
		const size_t t5 = line.find_first_of('\t', t4 + 2);
		const size_t t6 = line.find_first_of('\t', t5 + 2);
		const size_t t7 = line.find_first_of('\t', t6 + 2);
		const size_t t8 = line.find_first_of('\t', t7 + 2);
		const float mwt = lexical_cast<float>(line.substr(0, t1));
		const float logp = lexical_cast<float>(line.substr(t1 + 1, t2 - t1 - 1));
		const float ad = lexical_cast<float>(line.substr(t2 + 1, t3 - t2 - 1));
		const float pd = lexical_cast<float>(line.substr(t3 + 1, t4 - t3 - 1));
		const int hbd = lexical_cast<int>(line.substr(t4 + 1, t5 - t4 - 1));
		const int hba = lexical_cast<int>(line.substr(t5 + 1, t6 - t5 - 1));
		const float tpsa = lexical_cast<float>(line.substr(t6 + 1, t7 - t6 - 1));
		const int charge = lexical_cast<int>(line.substr(t7 + 1, t8 - t7 - 1));
		const int nrb = lexical_cast<int>(line.substr(t8 + 1));
		h_mwt[num_ligands] = mwt;
		h_logp[num_ligands] = logp;
		h_nrb[num_ligands] = nrb;
		h_hbd[num_ligands] = hbd;
		h_hba[num_ligands] = hba;
		h_charge[num_ligands] = charge;
		h_ad[num_ligands] = ad;
		h_pd[num_ligands] = pd;
		h_tpsa[num_ligands] = tpsa;
		++num_ligands;
*/
	}
	in.seekg(lexical_cast<size_t>(argv[3]));
	for (size_t i = 0; i < 1; ++i)
	{
		getline(fis, line);
		cout << line << '\n';
	}
/*
	free(h_mwt);
	free(h_logp);
	free(h_nrb);
	free(h_hbd);
	free(h_hba);
	free(h_charge);
	free(h_ad);
	free(h_pd);
	free(h_tpsa);
*/
	return 0;
}
