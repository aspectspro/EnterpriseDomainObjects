#include "payratedomainobject.h"

PayrateMapper PayrateFacade::mapper;

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

PayrateFacade::PayrateFacade() {
    connect(this,&PayrateFacade::employee_idChanged,[=](){
        load();
    });
}

QString PayrateFacade::getEmployee_id() const
{
    return employee_id;
}

void PayrateFacade::setEmployee_id(const QString &value)
{
    employee_id = value;
    emit employee_idChanged(value);
}

Money PayrateFacade::getPayrate() const
{
    return payrate;
}

void PayrateFacade::setPayrate(const Money &value)
{
    payrate = value;
    emit payrateChanged(value);
}

Money PayrateFacade::getOvertime_one() const
{
    return overtime_one;
}

void PayrateFacade::setOvertime_one(const Money &value)
{
    overtime_one = value;
    emit overtime_oneChanged(value);
}

Money PayrateFacade::getOvertime_two() const
{
    return overtime_two;
}

void PayrateFacade::setOvertime_two(const Money &value)
{
    overtime_two = value;
    emit overtime_twoChanged(value);
}

Money PayrateFacade::getOvertime_three() const
{
    return overtime_three;
}

void PayrateFacade::setOvertime_three(const Money &value)
{
    overtime_three = value;
    emit overtime_threeChanged(value);
}

void PayrateFacade::save()
{
    PayrateDomainObject pr;
    pr.setEmployee_id(getEmployee_id());
    pr.setOvertime_one(getOvertime_one());
    pr.setOvertime_two(getOvertime_two());
    pr.setOvertime_three(getOvertime_three());

    if(pr.getEmployee_id() == ""){
        qInfo() << "Must set employee id";
        return;
    }

    try {
        mapper.insert(pr);
    } catch (std::exception &e) {

        Q_UNUSED(e)
        try {
            mapper.update(pr);
        } catch (std::exception &e) {
            Q_UNUSED(e)
            qInfo() << "Couldn't save Payrate";
        }
    }
}

void PayrateFacade::load()
{
    try {
        auto pr = mapper.loadAll(QString("employee_id='%1'").arg(getEmployee_id())).first();
        setPayrate(pr.getPayrate());
        setOvertime_one(pr.getOvertime_one());
        setOvertime_two(pr.getOvertime_two());
        setOvertime_three(pr.getOvertime_three());
    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << QString("Couldn't load Payrate for '%1'").arg(getEmployee_id());
    }

}
