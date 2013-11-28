#include <iostream>
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
private:
	static const size_t n = 30;
	static const array<string, n> ad_strings;
	static const array<float, n> ad_covalent_radii;
public:
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
	"H", //  0
	"HD", //  1
	"C", //  2
	"A", //  3
	"N", //  4
	"NA", //  5
	"OA", //  6
	"S", //  7
	"SA", //  8
	"Se", //  9
	"P", // 10
	"F", // 11
	"Cl", // 12
	"Br", // 13
	"I", // 14
	"Zn", // 15
	"Fe", // 16
	"Mg", // 17
	"Ca", // 18
	"Mn", // 19
	"Cu", // 20
	"Na", // 21
	"K", // 22
	"Hg", // 23
	"Ni", // 24
	"Co", // 25
	"Cd", // 26
	"As", // 27
	"Sr", // 28
	"U", // 29
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
	1.276f, //  9 = Se, 1.276 = 1.1 * 1.16
	1.166f, // 10 = P , 1.166 = 1.1 * 1.06
	0.781f, // 11 = F , 0.781 = 1.1 * 0.71
	1.089f, // 12 = Cl, 1.089 = 1.1 * 0.99
	1.254f, // 13 = Br, 1.254 = 1.1 * 1.14
	1.463f, // 14 = I , 1.463 = 1.1 * 1.33
	1.441f, // 15 = Zn, 1.441 = 1.1 * 1.31
	1.375f, // 16 = Fe, 1.375 = 1.1 * 1.25
	1.430f, // 17 = Mg, 1.430 = 1.1 * 1.30
	1.914f, // 18 = Ca, 1.914 = 1.1 * 1.74
	1.529f, // 19 = Mn, 1.529 = 1.1 * 1.39
	1.518f, // 20 = Cu, 1.518 = 1.1 * 1.38
	1.694f, // 21 = Na, 1.694 = 1.1 * 1.54
	2.156f, // 22 = K , 2.156 = 1.1 * 1.96
	1.639f, // 23 = Hg, 1.639 = 1.1 * 1.49
	1.331f, // 24 = Ni, 1.331 = 1.1 * 1.21
	1.386f, // 25 = Co, 1.386 = 1.1 * 1.26
	1.628f, // 26 = Cd, 1.628 = 1.1 * 1.48
	1.309f, // 27 = As, 1.309 = 1.1 * 1.19
	2.112f, // 28 = Sr, 2.112 = 1.1 * 1.92
	2.156f, // 29 = U , 2.156 = 1.1 * 1.96
};

class frame
{
public:
	size_t parent; ///< Frame array index pointing to the parent of current frame. For ROOT frame, this field is not used.
	size_t rotorXsrn; ///< Serial atom number of the parent frame atom which forms a rotatable bond with the rotorY atom of current frame.
	size_t rotorYsrn; ///< Serial atom number of the current frame atom which forms a rotatable bond with the rotorX atom of parent frame.
	size_t rotorXidx; ///< Index pointing to the parent frame atom which forms a rotatable bond with the rotorY atom of current frame.
	size_t rotorYidx; ///< Index pointing to the current frame atom which forms a rotatable bond with the rotorX atom of parent frame.
	size_t childYidx; ///< The exclusive ending index to the heavy atoms of the current frame.
	bool active; ///< Indicates if the current frame is active.
	array<float, 3> yy; ///< Vector pointing from the origin of parent frame to the origin of current frame.
	array<float, 3> xy; ///< Normalized vector pointing from rotor X of parent frame to rotor Y of current frame.
	vector<size_t> branches; ///< Indexes to child branches.

	/// Constructs an active frame, and relates it to its parent frame.
	explicit frame(const size_t parent, const size_t rotorXsrn, const size_t rotorYsrn, const size_t rotorXidx, const size_t rotorYidx) : parent(parent), rotorXsrn(rotorXsrn), rotorYsrn(rotorYsrn), rotorXidx(rotorXidx), rotorYidx(rotorYidx), active(true) {}
};

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "extractnvfap 16_lig.pdbqt" << endl;
		return 0;
	}

	vector<frame> frames; ///< ROOT and BRANCH frames.
	vector<atom> atoms; ///< Heavy atoms. Coordinates are relative to frame origin, which is the first atom by default.
	vector<vector<size_t>> bonds; ///< Covalent bonds.
	frames.reserve(30); // A ligand typically consists of <= 30 frames.
	atoms.reserve(100); // A ligand typically consists of <= 100 heavy atoms.
	bonds.reserve(100); // A ligand typically consists of <= 100 heavy atoms.
	size_t nv; ///< Number of variables to optimize.
	size_t nf; ///< Number of frames.
	size_t na; ///< Number of atoms.
	size_t np; ///< Number of interacting pairs.
	size_t current;
	frame* f;
	string line;
	size_t n = 0;
	cout << "idx,nv,nf,na,np,lig,sln,cnf" << endl;
	for (ifstream ifs(argv[1]); getline(ifs, line);)
	{
		const string record = line.substr(0, 6);
		if (record == "ROOT")
		{
			frames.clear();
			atoms.clear();
			bonds.clear();

			frames.emplace_back(0, 0, 0, 0, 0); // ROOT is also treated as a frame. The parent, rotorXsrn, rotorYsrn, rotorXidx of ROOT frame are dummy.
			f = &frames.front(); // Pointer to the current frame.
			current = 0; // Index of current frame, initialized to ROOT frame.
			nv = 6;
			np = 0;
		}
		else if (record == "ATOM  " || record == "HETATM")
		{
			// Whenever an ATOM/HETATM line shows up, the current frame must be the last one.
			assert(current == frames.size() - 1);
			assert(f == &frames.back());

			// Parse the line.
			atom a(line);

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
					frames.emplace_back(current, rotorXsrn, rotorYsrn, i, atoms.size());
					break;
				}
			}

			// The current frame has the newly inserted BRANCH frame as one of its branches.
			// It is unsafe to use f in place of frames[current] because frames could reserve a new memory block after calling emplace_back().
			frames[current].branches.push_back(frames.size() - 1);

			// Now the current frame is the newly inserted BRANCH frame.
			current = frames.size() - 1;

			// Update the pointer to the current frame.
			f = &frames[current];

			// The ending index of atoms of previous frame is the starting index of atoms of current frame.
			frames[current - 1].childYidx = f->rotorYidx;
		}
		else if (record == "ENDBRA")
		{
			// If the current frame consists of rotor Y and a few hydrogens only, e.g. -OH, -NH2 or -CH3,
			// the torsion of this frame will have no effect on scoring and is thus redundant.
			if (current + 1 == frames.size() && f->rotorYidx + 1 == atoms.size())
			{
				f->active = false;
			}
			else
			{
				++nv;
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
			frames.back().childYidx = na = atoms.size();
			nf = frames.size();
			assert(nf >= 1 + nv - 6);

			// Find intra-ligand interacting pairs that are not 1-4.
			vector<size_t> neighbors;
			neighbors.reserve(10); // An atom typically consists of <= 10 neighbors.
			for (size_t k1 = 0; k1 < nf; ++k1)
			{
				const frame& f1 = frames[k1];
				for (size_t i = f1.rotorYidx; i < f1.childYidx; ++i)
				{
					// Find neighbor atoms within 3 consecutive covalent bonds.
					for (const size_t b1 : bonds[i])
					{
						if (find(neighbors.cbegin(), neighbors.cend(), b1) == neighbors.cend())
						{
							neighbors.push_back(b1);
						}
						for (const size_t b2 : bonds[b1])
						{
							if (find(neighbors.cbegin(), neighbors.cend(), b2) == neighbors.cend())
							{
								neighbors.push_back(b2);
							}
							for (const size_t b3 : bonds[b2])
							{
								if (find(neighbors.cbegin(), neighbors.cend(), b3) == neighbors.cend())
								{
									neighbors.push_back(b3);
								}
							}
						}
					}

					// Determine if interacting pairs can be possibly formed.
					for (size_t k2 = k1 + 1; k2 < nf; ++k2)
					{
						const frame& f2 = frames[k2];
						const frame& f3 = frames[f2.parent];
						for (size_t j = f2.rotorYidx; j < f2.childYidx; ++j)
						{
							if (k1 == f2.parent && (i == f2.rotorXidx || j == f2.rotorYidx)) continue;
							if (k1 > 0 && f1.parent == f2.parent && i == f1.rotorYidx && j == f2.rotorYidx) continue;
							if (f2.parent > 0 && k1 == f3.parent && i == f3.rotorXidx && j == f2.rotorYidx) continue;
							if (find(neighbors.cbegin(), neighbors.cend(), j) != neighbors.cend()) continue;
							++np;
						}
					}

					// Clear the current neighbor set for the next atom.
					neighbors.clear();
				}
			}
			const size_t lig_elems = 11 * nf + nf - 1 + 4 * na + 3 * np;
			const size_t sln_elems = (1 + nv + 1 + nv + 3 * nf + 4 * nf + 3 * na + 3 * na + 3 * nf + 3 * nf) * 3 + (nv * (nv + 1) >> 1) + nv * 3;
			const size_t cnf_elems = 1 + nv + 1;
			cout << n++ << ',' << nv << ',' << nf << ',' << na << ',' << np << ',' << lig_elems << ',' << sln_elems << ',' << cnf_elems << '\n';
		}
	}
}
