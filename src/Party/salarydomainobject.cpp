#include "salarydomainobject.h"
#include "person.h"

SalaryDomainObject::SalaryDomainObject()
{

}


const QMetaObject &SalaryDomainObject::metaObject() const
{
    return this->staticMetaObject;
}

void SalaryDomainObject::registerConverter()
{
}

QString SalaryDomainObject::getId() const
{
    return id;
}

void SalaryDomainObject::setId(const QString &value)
{
    id = value;
}

QString SalaryDomainObject::getEmployee_id() const
{
    return employee_id;
}

void SalaryDomainObject::setEmployee_id(const QString &value)
{
    employee_id = value;
}

Money SalaryDomainObject::getGross_pay() const
{
    return gross_pay;
}

void SalaryDomainObject::setGross_pay(const Money &value)
{
    gross_pay = value;
}

Money SalaryDomainObject::getNet_pay() const
{
    return net_pay;
}

void SalaryDomainObject::setNet_pay(const Money &value)
{
    net_pay = value;
}

Money SalaryDomainObject::getEmployee_nis() const
{
    return employee_nis;
}

void SalaryDomainObject::setEmployee_nis(const Money &value)
{
    employee_nis = value;
}

Money SalaryDomainObject::getEmployer_nis() const
{
    return employer_nis;
}

void SalaryDomainObject::setEmployer_nis(const Money &value)
{
    employer_nis = value;
}

Money SalaryDomainObject::getPaye() const
{
    return paye;
}

void SalaryDomainObject::setPaye(const Money &value)
{
    paye = value;
}

Money SalaryDomainObject::getHealth_surcharge() const
{
    return health_surcharge;
}

void SalaryDomainObject::setHealth_surcharge(const Money &value)
{
    health_surcharge = value;
}

DateTime SalaryDomainObject::getDate_from() const
{
    return date_from;
}

void SalaryDomainObject::setDate_from(const DateTime &value)
{
    date_from = value;
}

DateTime SalaryDomainObject::getDate_to() const
{
    return date_to;
}

void SalaryDomainObject::setDate_to(const DateTime &value)
{
    date_to = value;
}

DateTime SalaryDomainObject::getDate_paid() const
{
    return date_paid;
}

void SalaryDomainObject::setDate_paid(const DateTime &value)
{
    date_paid = value;
}

QString SalaryDomainMapper::tableName() const
{
    return "party_pay";
}


void SalaryDomainMapper::injectInsert(AbstractDomainObject &domainObject) const
{
    auto obj = dynamic_cast<SalaryDomainObject*>(&domainObject);

    auto where = QString("employee_id='%1' AND date_to >= %2")
            .arg(obj->getEmployee_id())
            .arg(obj->getDate_from().getTimestamp());
    QList<SalaryDomainObject> result;

    try {
        result = this->loadAll(where);
    } catch (std::exception &e) {
        Q_UNUSED(e);
    }

    if(result.count() >= 1){
        throw std::exception(
                    QString("Employee has been paid for date. Please set From Date later than '%1'")
                    .arg(obj->getDate_to().toIsoDate()).toUtf8());
    }
}
