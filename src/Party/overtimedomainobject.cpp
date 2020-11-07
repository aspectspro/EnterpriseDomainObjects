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

OvertimeFacade::OvertimeFacade() {
    load();
}

Double OvertimeFacade::getOvertime_rate_one() const
{
    return overtime_rate_one;
}

void OvertimeFacade::setOvertime_rate_one(const Double value)
{
    overtime_rate_one = value;
    emit overtime_rate_oneChanged(value);
}

Double OvertimeFacade::getOvertime_rate_two() const
{
    return overtime_rate_two;
}

void OvertimeFacade::setOvertime_rate_two(const Double value)
{
    overtime_rate_two = value;
    emit overtime_rate_twoChanged(value);
}

Double OvertimeFacade::getOvertime_rate_three() const
{
    return overtime_rate_three;
}

void OvertimeFacade::setOvertime_rate_three(const Double value)
{
    overtime_rate_three = value;
    emit overtime_rate_threeChanged(value);
}

void OvertimeFacade::save()
{
    OvertimeDomainObject ot;
    ot.setId("_this_");
    ot.setOvertime_rate_one(getOvertime_rate_one());
    ot.setOvertime_rate_two(getOvertime_rate_two());
    ot.setOvertime_rate_three(getOvertime_rate_three());

    try {
        mapper.insert(ot);
    } catch (std::exception &e) {
        mapper.update(ot);
        qInfo() << "Updating Overtime Settings";
    }

}

void OvertimeFacade::load()
{
    try {
        auto ot = mapper.find("_this_");
        setOvertime_rate_one(ot.getOvertime_rate_one());
        setOvertime_rate_two(ot.getOvertime_rate_two());
        setOvertime_rate_three(ot.getOvertime_rate_three());
    } catch (std::exception &e) {
        qInfo() << "Could not load Overtime Settings";
    }
}
