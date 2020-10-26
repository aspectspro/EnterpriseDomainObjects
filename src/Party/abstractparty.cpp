#include "abstractparty.h"

QString AbstractParty::getTelephone_number() const
{
    return telephone_number;
}

void AbstractParty::setTelephone_number(const QString value)
{
    telephone_number = value;
}

QString AbstractParty::getAddress() const
{
    return address;
}

void AbstractParty::setAddress(const QString value)
{
    address = value;
}

QString AbstractParty::getEmail_address() const
{
    return email_address;
}

void AbstractParty::setEmail_address(const QString value)
{
    email_address = value;
}

QString AbstractParty::getId() const
{
    return id;
}

void AbstractParty::setId(const QString value)
{
    id = value;
}

SetupModule &PartyModule::createModule()
{
    this->module = Module("Party",{1,0,0},{1,0,0});
    insertModule();
    return *this;
}

SetupModule &PartyModule::installSchema()
{
    auto baseTable = initializeModuleTable("abstractparty");
    baseTable.appendTableColumn({"id",TableColumn::TypeString,true});
    baseTable.appendTableColumn({"email_address",TableColumn::TypeString});
    baseTable.appendTableColumn({"telephone_number",TableColumn::TypeString});
    baseTable.appendTableColumn({"address",TableColumn::TypeString});
    baseTable.setPrimaryKey("id");
    insertTable(baseTable);

    auto organizationTable = initializeModuleTable("organization");
    organizationTable.appendTableColumn({"id",TableColumn::TypeString,true});
    organizationTable.appendTableColumn({"company_name",TableColumn::TypeString,true});
    insertTable(organizationTable);


//    QString first_name;
//    QString last_name;
//    QString identification_number;
//    QString driver_permit_number;
//    QString passport_number;
//    QDateTime date_of_birth;

    auto personTable = initializeModuleTable("person");
    personTable.appendTableColumn({"id",TableColumn::TypeString,true});
    personTable.appendTableColumn({"first_name",TableColumn::TypeString});
    personTable.appendTableColumn({"last_name",TableColumn::TypeString});
    personTable.appendTableColumn({"identification_number",TableColumn::TypeString,true});
    personTable.appendTableColumn({"driver_permit_number",TableColumn::TypeString,true});
    personTable.appendTableColumn({"passport_number",TableColumn::TypeString,true});
    personTable.appendTableColumn({"date_of_birth",TableColumn::TypeString,true});
    insertTable(personTable);

    return *this;
}

SetupModule &PartyModule::installData()
{
    return *this;
}

SetupModule &PartyModule::upgradeSchema()
{
    return *this;
}

SetupModule &PartyModule::upgradeData()
{
    return *this;
}
