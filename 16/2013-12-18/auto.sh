# Specify the beginning and ending slices
beg=0
end=126
# Download and unzip
curl -O http://zinc.docking.org/db/bysubset/16/16_prop.xls
curl -O http://zinc.docking.org/db/bysubset/16/16_purch.xls
for s in $(seq $beg $end); do
	slice=16_p0.$s
	curl -O http://zinc.docking.org/db/bysubset/16/$slice.mol2.gz
	gunzip $slice.mol2.gz
done
# Split mol2's that are not in 16_id.csv (7 hours required)
mkdir -p mol2 pdbqt
../../utilities/filtermol2 ../2013-01-10/16_id.csv $beg $end 16_id_new.csv
# Convert mol2 to pdbqt
cd mol2
for mol2 in mol2/*; do
	python2.5 ~/mgltools_x86_64Linux2_1.5.6/MGLToolsPckgs/AutoDockTools/Utilities24/prepare_ligand4.pyo -U '' -l $mol2 -o ../pdbqt/${mol2:0:8}.pdbqt
done
cd ..
# Update (3 hours required)
../../utilities/updatepdbqt ../2013-01-10/16_id.csv 16_id_new.csv 16_prop.xls 16_purch.xls ../2013-01-10/16_lig.pdbqt pdbqt 16_id.csv 16_hdr.bin 16_prop.tsv 16_prop.bin 16_lig.pdbqt minmax.csv
# Verify
n=$(wc -l < 16_id.csv)
echo "ligands: $n"
if [[ $[8 * n] != $(wc -c < 16_hdr.bin) ]]; then
	echo "16_hdr.bin file size not matched"
fi
if [[ 0 != $(../../utilities/seekheaders 16_lig.pdbqt 16_hdr.bin | wc -l) ]]; then
	echo "seekheaders 16_lig.pdbqt 16_hdr.bin failed"
fi
if [[ $[1 + n] != $(wc -l < 16_prop.tsv) ]]; then
	echo "16_prop.tsv line size not matched"
fi
if [[ $[26 * n] != $(wc -c < 16_prop.bin) ]]; then
	echo "16_prop.bin file size not matched"
fi
#tail -n +2 16_prop.xls  | cut -f1 | cut -d'C' -f2 > 16_prop_id.tsv
#tail -n +2 16_purch.xls | cut -f1 | cut -d'C' -f2 > 16_purch_id.tsv
#../../utilities/removeduplicates 16_prop_id.tsv 16_prop_id_unique.tsv
#../../utilities/removeduplicates 16_purch_id.tsv 16_purch_id_unique.tsv
#../../utilities/overlaysubset 16_id_new.id 16_prop_id_unique.tsv
#../../utilities/overlaysubset 16_id_new.id 16_purch_id_unique.tsv
# Gzip 16_prop.bin for use in web.js
gzip 16_prop.bin
# Plot property distributions
Rscript prop.R
# Clean up
rm -rf *.mol2 mol2 pdbqt
# Deploy updated files
mv *.png ~/istar/public/idock
scp 16_prop.bin.gz pc89066:/home/hjli/istar/idock
scp 16_lig.pdbqt proj74:/home/hjli/nfs/hjli/istar/idock
scp 16_hdr.bin proj74:/home/hjli/nfs/hjli/istar/idock
# Update minmax in web.js, index.html, index.js
