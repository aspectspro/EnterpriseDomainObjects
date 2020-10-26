#ifndef PARTYMODULE_H
#define PARTYMODULE_H
#include "AbstractObjects.h"
#include "database.h"
#include <iostream>

class PartyModule : public SetupModule{

protected:
    SetupModule &createModule() override;
    SetupModule &installSchema() override;
    SetupModule &installData() override;
    SetupModule &upgradeSchema() override;
    SetupModule &upgradeData() override;
};

#endif // PARTYMODULE_H
