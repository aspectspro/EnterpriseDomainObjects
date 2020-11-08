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

PayPeriod PaytypeDomainObject::getPay_period() const
{
    return pay_period;
}

void PaytypeDomainObject::setPay_period(const PayPeriod &value)
{
    pay_period = value;
}

EmploymentType PaytypeDomainObject::getEmployment_type() const
{
    return employment_type;
}

void PaytypeDomainObject::setEmployment_type(const EmploymentType &value)
{
    employment_type = value;
}

QString PaytypeMapper::tableName() const
{
    return "party_paytype";
}


EmploymentType::EmploymentType(){
    registerConverter();
}

const QMetaObject &EmploymentType::metaObject() const
{
    return staticMetaObject;
}

QString EmploymentType::getName() const
{
    return name;
}

void EmploymentType::setName(const QString &value)
{
    name = value;
}

QString EmploymentType::getId() const
{
    return id;
}

void EmploymentType::setId(const QString &value)
{
    id = value;
}


QString EmploymentTypeMapper::tableName() const
{
    return "party_employment_type";
}


PayPeriod::PayPeriod(){
    registerConverter();
}

const QMetaObject &PayPeriod::metaObject() const
{
    return staticMetaObject;
}

QString PayPeriod::getName() const
{
    return name;
}

void PayPeriod::setName(const QString &value)
{
    name = value;
}

QString PayPeriod::getId() const
{
    return id;
}

void PayPeriod::setId(const QString &value)
{
    id = value;
}


QString PayPeriodMapper::tableName() const
{
    return "party_pay_period";
}


void EmploymentType::registerConverter()
{
    if(QMetaType::hasRegisteredConverterFunction<EmploymentType,QString>())
        return;

    QMetaType::registerConverter<EmploymentType,QString>([=](EmploymentType empType) -> QString{
        return empType.getId();
    });

    QMetaType::registerConverter<QString,EmploymentType>([=](QString id) -> EmploymentType{
        EmploymentType type;
        type.setId(id);
        return type;
    });
}


void PayPeriod::registerConverter()
{
    if(QMetaType::hasRegisteredConverterFunction<PayPeriod,QString>())
        return;

    QMetaType::registerConverter<PayPeriod,QString>([=](PayPeriod payperiod) -> QString{
        return payperiod.getId();
    });

    QMetaType::registerConverter<QString,PayPeriod>([=](QString id) -> PayPeriod{
        PayPeriod type;
        type.setId(id);
        return type;
    });
}


void PaytypeMapper::injectLoad(AbstractDomainObject &domainObject) const
{
    static PayPeriodMapper payPeriodMapper;
    static EmploymentTypeMapper empMapper;

    auto paytype = dynamic_cast<PaytypeDomainObject*>(&domainObject);
    auto empType = empMapper.find(paytype->getEmployment_type().getId());
    auto payPeriod = payPeriodMapper.find(paytype->getPay_period().getId());
    paytype->setPay_period(payPeriod);
    paytype->setEmployment_type(empType);
}
