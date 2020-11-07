#include "overtimedomainobject.h"

OvertimeDomainObject::OvertimeDomainObject() {}

QString OvertimeDomainObject::getId() const
{
    return id;
}

void OvertimeDomainObject::setId(const QString &value)
{
    id = value;
}

Double OvertimeDomainObject::getOvertime_rate_two() const
{
    return overtime_rate_two;
}

void OvertimeDomainObject::setOvertime_rate_two(Double value)
{
    overtime_rate_two = value;
}

Double OvertimeDomainObject::getOvertime_rate_three() const
{
    return overtime_rate_three;
}

void OvertimeDomainObject::setOvertime_rate_three(const Double value)
{
    overtime_rate_three = value;
}

Double OvertimeDomainObject::getOvertime_rate_one() const
{
    return overtime_rate_one;
}

void OvertimeDomainObject::setOvertime_rate_one(Double value)
{
    overtime_rate_one = value;
}


const QMetaObject &OvertimeDomainObject::metaObject() const
{
    return staticMetaObject;
}


QString OvertimeMapper::tableName() const
{
    return "party_overtime_settings";
}


