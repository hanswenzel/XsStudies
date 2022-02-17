import sys
particle = "Pion+"
g4particle = "pi+"
plist = "QGSP_BERT"
energies = [ 50.0*j for j in range(1,41) ]
master = open( "run.sh", "w" )
tuples = open( "tuplelist.txt", "w" )

n = 0

for run in energies:
  out = open( "%s_%s_%03d.in" % (particle,plist,n), "w" )
  sys.stdout = out
  print("/control/verbose 1 ")
  print("/run/verbose 1 ")
  print("/tracking/verbose 0 ")
  print("")
  print("/testhadr/TargetMat G4_C ")
  print("/testhadr/TargetRadius 100 cm ")
  print("/testhadr/TargetLength 1 cm ")
  print("")
  print("/testhadr/Update ")
  print("/run/initialize ") 
  print("/random/setSeeds %d %d " % (n, 31+n))
  print("")
  print("/gun/particle %s " % g4particle)
  print("/gun/energy %2.1f MeV " % run)
  print("/run/beamOn 10000")
  sys.stdout = master
  print(" ./XsStudies %s_%s_%03d.in" % (particle,plist,n))
  sys.stdout = tuples
  print("ntuple_%04d.root" % n)

  n += 1

