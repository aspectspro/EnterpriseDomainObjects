#include "payratedomainobject.h"

PayrateDomainObject::PayrateDomainObject()
{

}


const QMetaObject &PayrateDomainObject::metaObject() const
{
    return staticMetaObject;
}

Money PayrateDomainObject::getPayrate() const
{
    return payrate;
}

void PayrateDomainObject::setPayrate(const Money &value)
{
    payrate = value;
}

Money PayrateDomainObject::getOvertime_one() const
{
    return overtime_one;
}

void PayrateDomainObject::setOvertime_one(const Money &value)
{
    overtime_one = value;
}

Money PayrateDomainObject::getOvertime_two() const
{
    return overtime_two;
}

void PayrateDomainObject::setOvertime_two(const Money &value)
{
    overtime_two = value;
}

Money PayrateDomainObject::getOvertime_three() const
{
    return overtime_three;
}

void PayrateDomainObject::setOvertime_three(const Money &value)
{
    overtime_three = value;
}

QString PayrateDomainObject::getEmployee_id() const
{
    return employee_id;
}

void PayrateDomainObject::setEmployee_id(const QString &value)
{
    employee_id = value;
}


QString PayrateMapper::tableName() const
{
    return "party_payrate";
}
