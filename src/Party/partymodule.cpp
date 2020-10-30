#include "partymodule.h"

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

SetupModule &PartyModule::createModule()
{
    this->module = Module("Party",{1,0,0},{1,0,0});
    insertModule();
    return *this;
}

SetupModule &PartyModule::installSchema()
{
//    Properties for AbstractParty
//    QString telephone_number;
//    QString address;
//    QString email_address;
//    QString id;

    auto baseTable = initializeModuleTable("abstractparty");
    baseTable.appendTableColumn({"id",TableColumn::TypeString,true});
    baseTable.appendTableColumn({"email_address",TableColumn::TypeString});
    baseTable.appendTableColumn({"telephone_number",TableColumn::TypeString});
    baseTable.appendTableColumn({"address",TableColumn::TypeString});
    baseTable.setPrimaryKey("id");
    insertTable(baseTable);

//    Properties for Organization
//    QString company_name;

    auto organizationTable = initializeModuleTable("organization");
    organizationTable.appendTableColumn({"id",TableColumn::TypeString,true});
    organizationTable.appendTableColumn({"company_name",TableColumn::TypeString,true});
    organizationTable.setPrimaryKey("id");
    insertTable(organizationTable);

//    Properties for Person
//    QString first_name;
//    QString last_name;
//    QString identification_number;
//    QString driver_permit_number;
//    QString passport_number;
//    QDateTime date_of_birth;

    auto personTable = initializeModuleTable("person");
    personTable.appendTableColumn({"id",TableColumn::TypeString,true});

    TableColumn first_name{"first_name",TableColumn::TypeString};
    first_name.setNotNull(true);
    first_name.setDefaultValue("");

    personTable.appendTableColumn(first_name);

    TableColumn last_name{"last_name",TableColumn::TypeString};
    last_name.setNotNull(true);
    last_name.setDefaultValue("");
    personTable.appendTableColumn(last_name);

    personTable.appendTableColumn({"identification_number",TableColumn::TypeString});
    personTable.appendTableColumn({"driver_permit_number",TableColumn::TypeString});
    personTable.appendTableColumn({"passport_number",TableColumn::TypeString});
    personTable.appendTableColumn({"date_of_birth",TableColumn::TypeInt});
    personTable.setPrimaryKey("id");
    insertTable(personTable);

//    Properties for Employee
//    QString bir_number;
//    QString nis_number;
//    DateTime date_of_employment;
//    DateTime date_of_discharge;

    auto employeeTable = initializeModuleTable("employee");
    employeeTable.appendTableColumn({"id",TableColumn::TypeString,true});
    employeeTable.appendTableColumn({"bir_number",TableColumn::TypeString});
    employeeTable.appendTableColumn({"nis_number",TableColumn::TypeString});
    employeeTable.appendTableColumn({"date_of_employment",TableColumn::TypeInt});
    employeeTable.appendTableColumn({"date_of_discharge",TableColumn::TypeInt});
    employeeTable.setPrimaryKey("id");
    insertTable(employeeTable);

    return *this;
}

