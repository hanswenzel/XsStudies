export PHYSLIST="FTFP_BERT"
for i in {100..700..50};
do
    echo "Number: $i";
    /bin/cat > run_pi-_${i}MeV_G4Ar.mac << EOF+ 
/control/verbose 1 
/run/verbose 1 
/tracking/verbose 0 

/testhadr/TargetMat G4_Ar
/testhadr/TargetRadius 100 cm 
/testhadr/TargetLength 1 cm 

/testhadr/Update 
/run/initialize 
/random/setSeeds 0 31 

/gun/particle pi- 
/gun/energy $i MeV 
/run/beamOn 1000000000
EOF+
./XsStudies run_pi-_${i}MeV_G4Ar.mac
mv B5.root G4Elastic_pi-_${i}MeV_G4Ar.root
done
export PHYSLIST="FTFP_BERT_TRV"
for i in {100..700..50};
do
    echo "Number: $i";
    /bin/cat > run_pi-_${i}MeV_G4Ar.mac << EOF+ 
/control/verbose 1 
/run/verbose 1 
/tracking/verbose 0 

/testhadr/TargetMat G4_Ar
/testhadr/TargetRadius 100 cm 
/testhadr/TargetLength 1 cm 

/testhadr/Update 
/run/initialize 
/random/setSeeds 0 31 

/gun/particle pi- 
/gun/energy $i MeV 
/run/beamOn 1000000000
EOF+
./XsStudies run_pi-_${i}MeV_G4Ar.mac
mv B5.root G4DiffuseElastic_pi-_${i}MeV_G4Ar.root
done