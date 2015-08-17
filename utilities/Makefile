CC=clang++ -std=c++11 -O2

all: benchmarkzip castprop checkheaders combinecolumns combinepdbqt combinesuppliers combinevendors countfiles countha counthac countheaders countligands countmwt decodeprop dumpligands extractligands extractlines extractnvfap extractpurch filterid filtermol2 filtermol2id filterxls findminmax insertprop insertsup overlaysubset parsecatalogs removeduplicates removehydrogens seekheaders smmm smmmf splitmol2 splitsdf updatepdbqt zincidtoindex statligand genheaderfrompdbqt encodeprop encodestat genheaderfromsdf genheaderfromtxt genfooterfrompdbqt genfooterfromsdf genfooterfromtxt encodeTypes decodeTypes inclusivescan

encodeTypes: encodeuint64 encodeint16 encodedouble encodefloat

decodeTypes: decodeuint64 decodeint16 decodedouble decodefloat

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

genheaderfrompdbqt: genheaderfrompdbqt.cpp
	$(CC) -o $@ $<

genfooterfrompdbqt: genfooterfrompdbqt.cpp
	$(CC) -o $@ $<

encodeprop: encodeprop.cpp
	$(CC) -o $@ $<

encodestat: encodestat.cpp
	$(CC) -o $@ $<

genheaderfromsdf: genheaderfromsdf.cpp
	$(CC) -o $@ $<

genfooterfromsdf: genfooterfromsdf.cpp
	$(CC) -o $@ $<

genheaderfromtxt: genheaderfromtxt.cpp
	$(CC) -o $@ $<

genfooterfromtxt: genfooterfromtxt.cpp
	$(CC) -o $@ $<

encodeuint64: encodeuint64.cpp
	$(CC) -o $@ $<

encodeint16: encodeint16.cpp
	$(CC) -o $@ $<

encodedouble: encodedouble.cpp
	$(CC) -o $@ $<

encodefloat: encodefloat.cpp
	$(CC) -o $@ $<

decodeuint64: decodeuint64.cpp
	$(CC) -o $@ $<

decodeint16: decodeint16.cpp
	$(CC) -o $@ $<

decodedouble: decodedouble.cpp
	$(CC) -o $@ $<

decodefloat: decodefloat.cpp
	$(CC) -o $@ $<

inclusivescan: inclusivescan.cpp
	$(CC) -o $@ $<
