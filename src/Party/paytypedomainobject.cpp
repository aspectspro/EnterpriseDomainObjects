#include "paytypedomainobject.h"


const QMetaObject &PaytypeDomainObject::metaObject() const
{
    return staticMetaObject;
}

QString PaytypeDomainObject::getId() const
{
    return id;
}

void PaytypeDomainObject::setId(const QString &value)
{
    id = value;
}

QString PaytypeDomainObject::getPay_period() const
{
    return pay_period;
}

void PaytypeDomainObject::setPay_period(const QString &value)
{
    pay_period = value;
}

QString PaytypeDomainObject::getEmployment_type() const
{
    return employment_type;
}

void PaytypeDomainObject::setEmployment_type(const QString &value)
{
    employment_type = value;
}


QString PaytypeMapper::tableName() const
{
    return "party_paytype";
}
