#include <iostream>
#include <string>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "filterxls 16_prop.xls mwt_lower_bound mwt_upper_bound\n";
		return 0;
	}

	using std::string;
	using boost::filesystem::ifstream;
	using boost::lexical_cast;

	const double mwt_lb = lexical_cast<double>(argv[2]);
	const double mwt_ub = lexical_cast<double>(argv[3]);

	string line;
	line.reserve(200);
	ifstream in(argv[1]);
	getline(in, line); // Header line.
	std::cout << line << '\n';
	while (getline(in, line))
	{
		const double mwt = lexical_cast<double>(line.substr(13, line.find_first_of('\t', 16) - 13));
		if (!(mwt > 350)) std::cout << line << '\n';
//		if ((mwt_lb <= mwt) && (mwt < mwt_ub)) std::cout << line << '\n';
	}
	in.close();
	return 0;
}

