#include "organization.h"

Organization::Organization()
{
    registerConverter();
}

QString Organization::getCompany_name() const
{
    return company_name;
}

void Organization::setCompany_name(const QString &value)
{
    company_name = value;
}

const QMetaObject &Organization::metaObject() const
{
    return staticMetaObject;
}

void Organization::registerConverter()
{
    qRegisterMetaType<Organization>();
}

void OrganizationMapper::injectInsert(AbstractDomainObject &domainObject) const
{
    AbstractPartyMapper mapper;
    mapper.insert(domainObject);
}

void OrganizationMapper::injectUpdate(AbstractDomainObject &domainObject) const
{
    AbstractPartyMapper mapper;
    mapper.update(domainObject);
}

void OrganizationMapper::injectRemove(AbstractDomainObject &domainObject) const
{
    AbstractPartyMapper mapper;
    mapper.remove(domainObject);
}

void OrganizationMapper::injectLoad(AbstractDomainObject &domainObject) const
{
    auto org = dynamic_cast<Organization*>(&domainObject);
    AbstractPartyMapper partyMapper;
    auto loadedParty = partyMapper.find(org->getId());
    org->copyFrom<AbstractParty>(domainObject);
}
