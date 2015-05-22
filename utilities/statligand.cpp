#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

/// Returns the square distance between two arrays.
float distance_sqr(const array<float, 3>& a, const array<float, 3>& b)
{
	const float d0 = a[0] - b[0];
	const float d1 = a[1] - b[1];
	const float d2 = a[2] - b[2];
	return d0 * d0 + d1 * d1 + d2 * d2;
}

class atom
{
public:
	static const size_t n = 14;
	static const array<string, n> ad_strings;
	static const array<float, n> ad_covalent_radii;
	static const array<float, n> ad_awt;
	size_t serial;
	array<float, 3> coord;
	size_t ad;

	// Constructs an atom from an ATOM/HETATM line in PDBQT format.
	explicit atom(const string& line) : serial(stoul(line.substr(6, 5))), ad(find(ad_strings.cbegin(), ad_strings.cend(), line.substr(77, isspace(line[78]) ? 1 : 2)) - ad_strings.cbegin())
	{
		coord[0] = stof(line.substr(30, 8));
		coord[1] = stof(line.substr(38, 8));
		coord[2] = stof(line.substr(46, 8));
	}

	bool ad_unsupported() const
	{
		return ad == n;
	}

	/// Returns true if the atom is a hydrogen atom.
	bool is_hydrogen() const
	{
		return ad <= 1;
	}

	/// Returns the covalent radius of current AutoDock4 atom type.
	float covalent_radius() const
	{
		return ad_covalent_radii[ad];
	}

	/// Returns true if the current atom is covalently bonded to a given atom.
	bool has_covalent_bond(const atom& a) const
	{
		const float s = covalent_radius() + a.covalent_radius();
		return distance_sqr(coord, a.coord) < s * s;
	}
};

/// AutoDock4 atom type names.
const array<string, atom::n> atom::ad_strings =
{
	"H",  //  0
	"HD", //  1
	"C",  //  2
	"A",  //  3
	"N",  //  4
	"NA", //  5
	"OA", //  6
	"S",  //  7
	"SA", //  8
	"P",  //  9
	"F",  // 10
	"Cl", // 11
	"Br", // 12
	"I",  // 13
};

/// AutoDock4 covalent radii, factorized by 1.1 for extra allowance.
const array<float, atom::n> atom::ad_covalent_radii =
{
	0.407f, //  0 = H , 0.407 = 1.1 * 0.37
	0.407f, //  1 = HD, 0.407 = 1.1 * 0.37
	0.847f, //  2 = C , 0.847 = 1.1 * 0.77
	0.847f, //  3 = A , 0.847 = 1.1 * 0.77
	0.825f, //  4 = N , 0.825 = 1.1 * 0.75
	0.825f, //  5 = NA, 0.825 = 1.1 * 0.75
	0.803f, //  6 = OA, 0.803 = 1.1 * 0.73
	1.122f, //  7 = S , 1.122 = 1.1 * 1.02
	1.122f, //  8 = SA, 1.122 = 1.1 * 1.02
	1.166f, //  9 = P , 1.166 = 1.1 * 1.06
	0.781f, // 10 = F , 0.781 = 1.1 * 0.71
	1.089f, // 11 = Cl, 1.089 = 1.1 * 0.99
	1.254f, // 12 = Br, 1.254 = 1.1 * 1.14
	1.463f, // 13 = I , 1.463 = 1.1 * 1.33
};

/// AutoDock4 atomic weight.
const array<float, atom::n> atom::ad_awt =
{
	  1.008, //  0
	  1.008, //  1
	 12.01,  //  2
	 12.01,  //  3
	 14.01,  //  4
	 14.01,  //  5
	 16.00,  //  6
	 32.07,  //  7
	 32.07,  //  8
	 30.97,  //  9
	 19.00,  // 10
	 35.45,  // 11
	 79.90,  // 12
	126.90,  // 13
};

class frame
{
public:
	size_t parent; ///< Frame array index pointing to the parent of current frame. For ROOT frame, this field is not used.
	size_t rotorXidx; ///< Index pointing to the parent frame atom which forms a rotatable bond with the rotorY atom of current frame.
	size_t rotorYidx; ///< Index pointing to the current frame atom which forms a rotatable bond with the rotorX atom of parent frame.

	/// Constructs an active frame, and relates it to its parent frame.
	explicit frame(const size_t parent, const size_t rotorXidx, const size_t rotorYidx) : parent(parent), rotorXidx(rotorXidx), rotorYidx(rotorYidx) {}
};

int main(int argc, char* argv[])
{
	cout.setf(ios::fixed, ios::floatfield);
	cout << setprecision(3);
	vector<frame> frames; ///< ROOT and BRANCH frames.
	vector<atom> atoms; ///< Heavy atoms. Coordinates are relative to frame origin, which is the first atom by default.
	vector<vector<size_t>> bonds; ///< Covalent bonds.
	frames.reserve(50); // A ligand typically consists of <= 50 frames.
	atoms.reserve(200); // A ligand typically consists of <= 200 heavy atoms.
	bonds.reserve(200); // A ligand typically consists of <= 200 heavy atoms.
	array<size_t, atom::n> counters; // Counters of each AutoDock4 type.
	size_t nat; ///< Number of active torsions.
	size_t current;
	frame* f;
	string zid;
	size_t lineno = 0, ligandno = 0;
	for (string line; getline(cin, line);)
	{
		++lineno;
		const string record = line.substr(0, 6);
		if (record == "REMARK")
		{
			++ligandno;
			zid = line.substr(11, 8);
			getline(cin, line);
			getline(cin, line);
		}
		else if (record == "ROOT")
		{
			frames.clear();
			atoms.clear();
			bonds.clear();
			counters.fill(0);
			nat = 0;

			frames.emplace_back(0, 0, 0); // ROOT is also treated as a frame. The parent, rotorXsrn, rotorYsrn, rotorXidx of ROOT frame are dummy.
			f = &frames.front(); // Pointer to the current frame.
			current = 0; // Index of current frame, initialized to ROOT frame.
		}
		else if (record == "ATOM  " || record == "HETATM")
		{
			// Whenever an ATOM/HETATM line shows up, the current frame must be the last one.
			assert(current == frames.size() - 1);
			assert(f == &frames.back());

			// Parse the line.
			atom a(line);
			assert(!a.ad_unsupported());

			++counters[a.ad];

			if (a.is_hydrogen()) continue;

			// Find bonds between the current atom and the other atoms of the same frame.
			assert(bonds.size() == atoms.size());
			bonds.emplace_back();
			bonds.back().reserve(4); // An atom typically consists of <= 4 bonds.
			for (size_t i = atoms.size(); i > f->rotorYidx;)
			{
				atom& b = atoms[--i];
				if (a.has_covalent_bond(b))
				{
					bonds[atoms.size()].push_back(i);
					bonds[i].push_back(atoms.size());
				}
			}

			// Save the heavy atom.
			atoms.push_back(move(a));
		}
		else if (record == "BRANCH")
		{
			// Parse "BRANCH   X   Y". X and Y are right-justified and 4 characters wide.
			const size_t rotorXsrn = stoul(line.substr( 6, 4));
			const size_t rotorYsrn = stoul(line.substr(10, 4));

			// Find the corresponding heavy atom with x as its atom serial number in the current frame.
			for (size_t i = f->rotorYidx; true; ++i)
			{
				if (atoms[i].serial == rotorXsrn)
				{
					// Insert a new frame whose parent is the current frame.
					frames.emplace_back(current, i, atoms.size());
					break;
				}
			}

			// Now the current frame is the newly inserted BRANCH frame.
			current = frames.size() - 1;

			// Update the pointer to the current frame.
			f = &frames[current];
		}
		else if (record == "ENDBRA")
		{
			// If the current frame consists of rotor Y and a few hydrogens only, e.g. -OH, -NH2 or -CH3,
			// the torsion of this frame will have no effect on scoring and is thus redundant.
			if (current + 1 == frames.size() && f->rotorYidx + 1 == atoms.size())
			{
			}
			else
			{
				++nat;
			}

			// Set up bonds between rotorX and rotorY.
			bonds[f->rotorYidx].push_back(f->rotorXidx);
			bonds[f->rotorXidx].push_back(f->rotorYidx);

			// Now the parent of the following frame is the parent of current frame.
			current = f->parent;

			// Update the pointer to the current frame.
			f = &frames[current];
		}
		else if (record == "TORSDO")
		{
			assert(current == 0); // current should remain its original value if "BRANCH" and "ENDBRANCH" properly match each other.
			assert(f == &frames.front()); // The frame pointer should remain its original value if "BRANCH" and "ENDBRANCH" properly match each other.
			float mwt = 0;
			size_t na = 0;
			for (size_t i = 0; i < atom::n; ++i)
			{
				mwt += atom::ad_awt[i] * counters[i];
				na += counters[i];
			}
			assert(na == atoms.size() + counters[0] + counters[1]);
			const size_t hbd = counters[1];
			const size_t hba = counters[5] + counters[6] + counters[8];
			const size_t torsdof = stoul(line.substr(8));
			const size_t nts = frames.size() - 1; // In most cases, torsdof == nts. In some cases, torsdof == frames.size(). So, do not rely on the TORSDOF value.
			size_t nhc = counters[2] + counters[3];
			for (size_t k = 0; k < bonds.size(); ++k)
			{
				if (atoms[k].ad > 3) continue;
				bool hydrophobic = true;
				for (const auto& ai : bonds[k])
				{
					if (atoms[ai].ad > 3)
					{
						hydrophobic = false;
						break;
					}
				}
				if (!hydrophobic) --nhc;
			}
			assert(nhc <= atoms.size());
			for (const auto c : counters) cout << c << '\t';
			cout << na << '\t' << atoms.size() << '\t' << hbd << '\t' << hba << '\t' << nhc << '\t' << nts << '\t' << nat << '\t' << mwt << endl;
		}
	}
}
