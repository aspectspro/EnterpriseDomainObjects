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

const QMetaObject &Person::metaObject() const
{
    return staticMetaObject;
}

void Person::registerConverter()
{
    qRegisterMetaType<Person>();
}

QString Person::getFirst_name() const
{
    return first_name;
}

void Person::setFirst_name(const QString value)
{
    first_name = value;
}

QString Person::getLast_name() const
{
    return last_name;
}

void Person::setLast_name(const QString value)
{
    last_name = value;
}

QString Person::getIdentification_number() const
{
    return identification_number;
}

void Person::setIdentification_number(const QString value)
{
    identification_number = value;
}

QString Person::getDriver_permit_number() const
{
    return driver_permit_number;
}

void Person::setDriver_permit_number(const QString value)
{
    driver_permit_number = value;
}

QString Person::getPassport_number() const
{
    return passport_number;
}

void Person::setPassport_number(const QString value)
{
    passport_number = value;
}

QDateTime Person::getDate_of_birth() const
{
    return date_of_birth;
}

void Person::setDate_of_birth(const QDateTime value)
{
    date_of_birth = value;
}
