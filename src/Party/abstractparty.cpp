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
//    organizationTable.appendTableColumn({"party_id",TableColumn::TypeString});
    organizationTable.appendTableColumn({"company_name",TableColumn::TypeString});
    insertTable(organizationTable);

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

QString Organization::getCompany_name() const
{
    return company_name;
}

void Organization::setCompany_name(const QString &value)
{
    company_name = value;
}

//QString Organization::getParty_id() const
//{
//    return party_id;
//}

//void Organization::setParty_id(const QString &value)
//{
//    party_id = value;
//}

void OrganizationMapper::injectInsert(AbstractDomainObject &domainObject) const
{
    auto org = dynamic_cast<Organization*>(&domainObject);
    AbstractParty party(*org);
    party.generateId();

    AbstractPartyMapper mapper;
    mapper.insert(party);

    org->setId(party.getId());
}

void OrganizationMapper::injectUpdate(AbstractDomainObject &domainObject) const
{
    auto org = dynamic_cast<Organization*>(&domainObject);
    AbstractParty party(*org);
    AbstractPartyMapper mapper;
    mapper.update(party);
}

void OrganizationMapper::injectRemove(AbstractDomainObject &domainObject) const
{
    auto org = dynamic_cast<Organization*>(&domainObject);
    AbstractPartyMapper mapper;
    mapper.remove(*org);
}

void OrganizationMapper::injectLoad(AbstractDomainObject &domainObject) const
{
    auto org = dynamic_cast<Organization*>(&domainObject);
    AbstractPartyMapper partyMapper;
    auto loadedParty = partyMapper.find(org->getId());
    org->copyBaseParty(loadedParty);
}
