# Specify the beginning and ending slices
beg=0
end=126
# Download and unzip 16_*. The newly-added ligands are distributed among the slices. Therefore all slices must be downloaded.
curl -O http://zinc.docking.org/db/bysubset/16/16_prop.xls
curl -O http://zinc.docking.org/db/bysubset/16/16_purch.xls
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
printf "10.0.32.1\n10.0.32.2\n10.0.32.3\n10.0.32.4\n10.0.32.5\n" > hosts
echo "nohup ./convert.sh  > convert-\${MV2_COMM_WORLD_RANK}.out 2> convert-\${MV2_COMM_WORLD_RANK}.err < /dev/null &" > nohup.sh
mpirun_rsh -hostfile hosts -n 5 nohup.sh
for s in $(seq ${MV2_COMM_WORLD_RANK} ${MV2_COMM_WORLD_SIZE} $end); do
	echo Converting 16_p0.$s
	mkdir -p 16_p0.$s.pdbqt
	for id in $(cat 16_p0.$s.csv); do
		python2.5 ${MGLTOOLS_ROOT}/MGLToolsPckgs/AutoDockTools/Utilities24/prepare_ligand4.pyo -U '' -l 16_p0.$s/$id.mol2 -o 16_p0.$s.pdbqt/$id.pdbqt
	done
done
# Update 16_lig.pdbqt. This step requires 3 hours.
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
scp 16_lig.pdbqt 16_hdr.bin proj74:/home/hjli/nfs/hjli/istar/idock
# Update minmax in web.js, public/idock/index.html, public/idock/index.js
