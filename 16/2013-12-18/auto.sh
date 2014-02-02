# Specify the beginning and ending slices. The following steps can be parallelized by subdividing $(seq $beg $end).
beg=0
end=126
# Download and unzip 16_p0.*.mol2.gz. The newly-added ligands are distributed among the slices. Therefore all slices must be downloaded.
for s in $(seq $beg $end); do
	curl -s http://zinc.docking.org/db/bysubset/16/16_p0.$s.mol2.gz | gunzip > 16_p0.$s.mol2
done
# Split mol2's that are not in 16_id.csv. File stems are 8 characters wide, without the ZINC prefix. Output csv contains (id, slice). This step requires 7 hours.
for s in $(seq $beg $end); do
	mkdir -p 16_p0.$s.m
done
../../utilities/filtermol2 ../2013-01-10/16_id.csv $beg $end
sort -t, -k1,1 16_p0.*.csv | tee >(cut -d, -f1 > 16_nid.csv) >(cut -d, -f2 > 16_nss.csv) | uniq -d | xargs -I {} grep {} 16_p0.*.csv
# Convert mol2 to pdbqt. This step requires a few days.
for s in $(seq 0 6 $end); do
	echo 16_p0.$s
	mkdir -p 16_p0.$s.p
	for c in $(cat 16_p0.$s.csv); do
		z=${c:0:8}
		python2.5 ${MGLTOOLS_ROOT}/MGLToolsPckgs/AutoDockTools/Utilities24/prepare_ligand4.pyo -U '' -l 16_p0.$s.m/$z.mol2 -o 16_p0.$s.p/$z.pdbqt
	done
done
# Update 16_lig.pdbqt. Progress can be checked by ls -lht. This step requires 3 hours.
curl -O http://zinc.docking.org/db/bysubset/16/16_prop.xls
curl -O http://zinc.docking.org/db/bysubset/16/16_purch.xls
../../utilities/updatepdbqt ../2013-01-10/16_id.csv 16_nid.csv 16_nss.csv 16_prop.xls 16_purch.xls ../2013-01-10/16_lig.pdbqt 16_id.csv 16_hdr.bin 16_prop.tsv 16_prop.bin 16_lig.pdbqt minmax.csv
rm 16_prop.xls 16_purch.xls 16_nid.csv 16_nss.csv
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
# Clean up
rm -rf 16_p0.*
# Gzip 16_prop.bin for use in web.js
gzip 16_prop.bin
# Plot property distributions
Rscript prop.R
# Deploy updated files
mv *.png ~/istar/public/idock
scp 16_prop.bin.gz pc89066:/home/hjli/istar/idock
scp 16_lig.pdbqt 16_hdr.bin hpc5:/home/hjli/nfs/hjli/istar/idock
# Update num_ligands in idock/src/main.cpp
# Update minmax in web.js, public/idock/index.html, public/idock/index.js
../../utilities/extractnvfap 16_lig.pdbqt > 16_nvfap.csv 2> extractnvfap.err
tail -n +2 16_nvfap.csv | cut -d, -f6- | ../../utilities/smmm
# Update idock/src/main_cp.cpp, main_cu.cpp, main_cl.cpp
