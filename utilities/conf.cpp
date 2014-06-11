#include <iostream>
#include <GraphMol/MolOps.h>
#include <GraphMol/FileParsers/MolSupplier.h>
#include <GraphMol/FileParsers/MolWriters.h>
#include <GraphMol/Descriptors/Lipinski.h>
#include <GraphMol/DistGeomHelpers/Embedder.h>
#include <GraphMol/ForceFieldHelpers/UFF/Builder.h>
#include <ForceField/ForceField.h>
using namespace std;
using namespace RDKit;
using namespace RDKit::MolOps;
using namespace RDKit::Descriptors;
using namespace RDKit::DGeomHelpers;
using namespace RDKit::UFF;

int main()
{
	SDWriter writer(&cout);
	for (SmilesMolSupplier sup(&cin, false, "\t", 1, 0); !sup.atEnd();)
	{
		const auto mol = addHs(*sup.next());
		const auto nrot = calcNumRotatableBonds(*mol);
		const auto numConfs = nrot <= 7 ? 50 : (nrot <= 12 ? 200 : 300);
		for (const auto id : EmbedMultipleConfs(*mol, numConfs))
		{
			auto ff = constructForceField(*mol, 100.0, id);
			ff->initialize();
			ff->minimize();
			const auto e = ff->calcEnergy();
//			writer.write(*mol, id);
		}
	}
}
