# Specify the beginning and ending slices
beg=0
end=126
# Download and unzip 16_*. The newly-added ligands are distributed among the slices. Therefore all slices must be downloaded.
for s in $(seq $beg $end); do
	curl -s http://zinc.docking.org/db/bysubset/16/16_p0.$s.mol2.gz | gunzip > 16_p0.$s.mol2
done
# Split mol2's that are not in 16_id.csv. File stems are 8 characters wide, without the ZINC prefix. This step requires 7 hours, and can be parallelized by subdividing {$beg..$end}.
for s in $(seq $beg $end); do
	mkdir -p 16_p0.$s
done
../../utilities/filtermol2 ../2013-01-10/16_id.csv $beg $end
sort 16_p0.*.csv | tee 16_id_new.csv | uniq -d | xargs -I {} grep {} 16_p0.*.csv
# Convert mol2 to pdbqt. This step requires a few days, and can be parallelized.
for s in $(seq 0 6 $end); do
	echo 16_p0.$s
	mkdir -p 16_p0.$s.pdbqt
	for z in $(cat 16_p0.$s.csv); do
		python2.5 ${MGLTOOLS_ROOT}/MGLToolsPckgs/AutoDockTools/Utilities24/prepare_ligand4.pyo -U '' -l 16_p0.$s/$z.mol2 -o 16_p0.$s.pdbqt/$z.pdbqt
	done
done
# Create 16_id_slice.csv
for s in $(seq $beg $end); do
	echo $s
	c=$(wc -l < 16_p0.$s.csv)
	for i in $(seq 1 $c); do
		echo $s >> 16_p0.$s.slice.csv
	done
	paste -d, 16_p0.$s.csv 16_p0.$s.slice.csv > 16_p0.$s.id+slice.csv
	rm 16_p0.$s.slice.csv
done
sort 16_p0.*.id+slice.csv -t, -k1,1 | cut -d, -f2 > 16_id_slice.csv
rm 16_p0.*.id+slice.csv
# Update 16_lig.pdbqt. This step requires 3 hours. Progress can be checked by ls -lht.
curl -O http://zinc.docking.org/db/bysubset/16/16_prop.xls
curl -O http://zinc.docking.org/db/bysubset/16/16_purch.xls
../../utilities/updatepdbqt ../2013-01-10/16_id.csv 16_id_new.csv 16_id_slice.csv 16_prop.xls 16_purch.xls ../2013-01-10/16_lig.pdbqt 16_id.csv 16_hdr.bin 16_prop.tsv 16_prop.bin 16_lig.pdbqt minmax.csv
rm 16_prop.xls 16_purch.xls 16_id_new.csv 16_id_slice.csv
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
# Gzip 16_prop.bin for use in web.js
gzip 16_prop.bin
# Plot property distributions
Rscript prop.R
# Clean up
rm -rf *.mol2 16_p0.*
# Deploy updated files
mv *.png ~/istar/public/idock
scp 16_prop.bin.gz pc89066:/home/hjli/istar/idock
scp 16_lig.pdbqt 16_hdr.bin proj74:/home/hjli/nfs/hjli/istar/idock
# Update minmax in web.js, public/idock/index.html, public/idock/index.js
# Update num_ligands in idock/src/main.cpp
../../utilities/extractnvfap 16_lig.pdbqt > 16_nvfap.csv 2> extractnvfap.err
tail -n +2 16_nvfap.csv | cut -d, -f6- | ../../utilities/smmm
# Update idock/src/main_cp.cpp, main_cu.cpp, main_cl.cpp
