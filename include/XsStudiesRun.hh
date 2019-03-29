/* 
 * File:   Run.hh
 * Author: wenzel
 *
 * Created on March 6, 2019, 11:02 AM
 */

#ifndef RUN_HH
#define RUN_HH

#include "globals.hh"
#include "G4Run.hh"

//
// Forward declarations
//
class G4Event;
class G4ParticleDefinition;
class XsStudiesPrimaryGeneratorAction;

class XsStudiesRun : public G4Run {
public:
    XsStudiesRun();
    virtual ~XsStudiesRun();
    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);
    void EndOfRun();
    void SetNumberinElastic(unsigned int numberinElastic);
    unsigned int GetNumberinElastic() const;
    void SetNumberElastic(unsigned int numberElastic);
    unsigned int GetNumberElastic() const;
    void SetNrEvents(unsigned int NrEvents);
    unsigned int GetNrEvents() const;
private:
    G4double energy;
    G4ParticleDefinition* particle;
    const XsStudiesPrimaryGeneratorAction* primary;
    unsigned int NrEvents;
    unsigned int numberElastic;
    unsigned int numberinElastic;
};

#endif /* RUN_HH */
