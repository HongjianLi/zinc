#!/usr/bin/env python2
from rdkit import Chem
from rdkit.Chem import AllChem
from rdkit.Chem import rdMolDescriptors

writer = Chem.SDWriter("16.sdf")
sup = Chem.SmilesMolSupplier("16.smi", delimiter='\t', smilesColumn=1, nameColumn=0)
for mol in sup:
	mol = Chem.AddHs(mol)
	nrot = rdMolDescriptors.CalcNumRotatableBonds(mol)
	numConfs = 50 if nrot <= 7 else 200 if nrot <= 12 else 300
	numConfs = 2
	for id in AllChem.EmbedMultipleConfs(mol, numConfs):
#		AllChem.UFFOptimizeMolecule(mol, confId=id)
		ff = AllChem.UFFGetMoleculeForceField(mol, confId=id)
		ff.Initialize()
		ff.Minimize()
		e = ff.CalcEnergy()
		rmsd = AllChem.GetBestRMS(mol, mol, 0, id)
		writer.write(mol, confId=id)
