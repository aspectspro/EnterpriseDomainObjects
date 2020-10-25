#include "organization.h"

QString Organization::getCompany_name() const
{
    return company_name;
}

void Organization::setCompany_name(const QString &value)
{
    company_name = value;
}

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
