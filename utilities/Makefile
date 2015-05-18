CC=clang++ -std=c++11 -O2

all: benchmarkzip castprop checkheaders combinecolumns combinepdbqt combinesuppliers combinevendors countfiles countha counthac countheaders countligands countmwt decodeprop dumpligands encodehdr extractligands extractlines extractnvfap extractpurch filterid filtermol2 filtermol2id filterxls findminmax insertprop insertsup overlaysubset parsecatalogs removeduplicates removehydrogens seekheaders smmm smmmf splitmol2 splitsdf updatepdbqt zincidtoindex statligand

benchmarkzip: benchmarkzip.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem -lboost_iostreams -lboost_timer

castprop: castprop.cpp
	$(CC) -o $@ $< -lboost_system -lboost_timer

checkheaders: checkheaders.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

combinecolumns: combinecolumns.cpp
	$(CC) -o $@ $<

combinepdbqt: combinepdbqt.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

combinesuppliers: combinesuppliers.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

combinevendors: combinevendors.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

countfiles: countfiles.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

countha: countha.cpp
	$(CC) -o $@ $<

counthac: counthac.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

countheaders: countheaders.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

countligands: countligands.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

countmwt: countmwt.cpp
	$(CC) -o $@ $<

decodeprop: decodeprop.cpp
	$(CC) -o $@ $< -lboost_system -lboost_timer

dumpligands: dumpligands.cpp
	$(CC) -o $@ $<

encodehdr: encodehdr.cpp
	$(CC) -o $@ $<

extractligands: extractligands.cpp
	$(CC) -o $@ $<

extractlines: extractlines.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

extractnvfap: extractnvfap.cpp
	$(CC) -o $@ $<

extractpurch: extractpurch.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

filterid: filterid.cpp
	$(CC) -o $@ $<

filtermol2: filtermol2.cpp
	$(CC) -o $@ $<

filtermol2id: filtermol2id.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

filterxls: filterxls.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

findminmax: findminmax.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

insertprop: insertprop.cpp
	$(CC) -o $@ $<

insertsup: insertsup.cpp
	$(CC) -o $@ $<

overlaysubset: overlaysubset.cpp
	$(CC) -o $@ $<

parsecatalogs: parsecatalogs.cpp
	$(CC) -o $@ $< -lboost_system -lboost_filesystem

removeduplicates: removeduplicates.cpp
	$(CC) -o $@ $<

removehydrogens: removehydrogens.cpp
	$(CC) -o $@ $<

seekheaders: seekheaders.cpp
	$(CC) -o $@ $<

smmm: smmm.cpp
	$(CC) -o $@ $<

smmmf: smmmf.cpp
	$(CC) -o $@ $<

splitmol2: splitmol2.cpp
	$(CC) -o $@ $<

splitsdf: splitsdf.cpp
	$(CC) -o $@ $<

updatepdbqt: updatepdbqt.cpp
	$(CC) -o $@ $<

zincidtoindex: zincidtoindex.cpp
	$(CC) -o $@ $<

statligand: statligand.cpp
	$(CC) -o $@ $<
