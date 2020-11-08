#include "paytypedomainobject.h"

EmploymentTypeMapper EmploymentTypeFacade::mapper;
PaytypeMapper PaytypeFacade::mapper;

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

bool EmploymentType::operator==(const EmploymentType &empType)
{
    return (empType.getId() == getId() && empType.getName() == getName());
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

bool PayPeriod::operator==(const PayPeriod &period)
{
    return (period.getId() == getId() && getName() == period.getName());
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
    PayPeriodMapper payPeriodMapper;
    EmploymentTypeMapper empMapper;

    auto paytype = dynamic_cast<PaytypeDomainObject*>(&domainObject);

    auto empType = empMapper.find(paytype->getEmployment_type().getId());
    auto payPeriod = payPeriodMapper.find(paytype->getPay_period().getId());

    paytype->setPay_period(payPeriod);
    paytype->setEmployment_type(empType);
}

EmploymentTypeFacade::EmploymentTypeFacade(){

    initializeEmploymentTypes();

    connect(this,&EmploymentTypeFacade::idChanged,[=](EmploymentTypeEnum id){
        Q_UNUSED(id);
        load();
    });
}

QString EmploymentTypeFacade::getName() const
{
    return name;
}

void EmploymentTypeFacade::setName(const QString &value)
{
    name = value;
    emit nameChanged(value);
}

EmploymentTypeFacade::EmploymentTypeEnum EmploymentTypeFacade::getId() const
{
    return this->id;
}

void EmploymentTypeFacade::setId(const EmploymentTypeEnum value)
{
    id = value;
    emit idChanged(value);
}

void EmploymentTypeFacade::load()
{
    try {
        auto empType = mapper.find(QString::number(id));
        setName(empType.getName());
    } catch (std::exception &e) {
        qInfo() << e.what() << "Employment Type Could not be loaded";
    }

}

void EmploymentTypeFacade::initializeEmploymentTypes()
{
    EmploymentType hourly;
    hourly.setId(QString::number(HOURLY));
    hourly.setName("Hourly");

    EmploymentType salaried;
    salaried.setId(QString::number(SALARIED));
    salaried.setName("Salaried");

    EmploymentType commissioned;
    commissioned.setId(QString::number(COMMISSIONED));
    commissioned.setName("Commissioned");


    try {
        mapper.insert(hourly);
        mapper.insert(salaried);
        mapper.insert(commissioned);
    } catch (std::exception &e) {
        Q_UNUSED(e);
    }

}

PayPeriodMapper PayPeriodFacade::mapper;

PayPeriodFacade::PayPeriodFacade() {
    initializePayPeriod();
    connect(this,&PayPeriodFacade::idChanged,[=](PayPeriodEnum payPeriod){
        Q_UNUSED(payPeriod);
        load();
    });
}

PayPeriodFacade::PayPeriodEnum PayPeriodFacade::getId() const
{
    return id;
}

void PayPeriodFacade::setId(const PayPeriodEnum value)
{
    id = value;
    emit idChanged(value);
}

QString PayPeriodFacade::getName() const
{
    return name;
}

void PayPeriodFacade::setName(const QString &value)
{
    name = value;
    emit nameChanged(value);
}

void PayPeriodFacade::load()
{
    try {
        auto payPeriod = mapper.find(QString::number(getId()));
        setName(payPeriod.getName());
    } catch (std::exception &e) {
        qInfo() << e.what() << "Couldn't load pay period";
    }

}

void PayPeriodFacade::initializePayPeriod()
{
    PayPeriod daily;
    daily.setId(QString::number(DAILY));
    daily.setName("Daily");

    PayPeriod weekly;
    weekly.setId(QString::number(WEEKLY));
    weekly.setName("Weekly");

    PayPeriod fortnightly;
    fortnightly.setId(QString::number(FORTNIGHTLY));
    fortnightly.setName("Fortnighly");


    PayPeriod monthly;
    monthly.setId(QString::number(MONTHLY));
    monthly.setName("Monthly");

    try {
        mapper.insert(daily);
        mapper.insert(weekly);
        mapper.insert(fortnightly);
        mapper.insert(monthly);
    } catch (std::exception &e) {
        Q_UNUSED(e);
//        qInfo() << e.what();
    }
}

PaytypeFacade::PaytypeFacade() {

    PayPeriodFacade::initializePayPeriod();
    EmploymentTypeFacade::initializeEmploymentTypes();

    connect(this,&PaytypeFacade::idChanged,[=](QString id){
        Q_UNUSED(id);
        load();
    });
}

QString PaytypeFacade::getId() const
{
    return id;
}

void PaytypeFacade::setId(const QString &value)
{
    id = value;
    emit idChanged(value);
}

void PaytypeFacade::load()
{
    try {
        PaytypeMapper mapper;
        auto pt = mapper.find(getId());

        setPayPeriod(pt.getPay_period().getId().toInt());
        setEmploymentType(pt.getEmployment_type().getId().toInt());

    } catch (std::exception &e) {

        qInfo() << e.what() << QString("Couldn't load Paytype '%1'").arg(getId());
    }
}

void PaytypeFacade::save()
{
    PaytypeDomainObject paytype;
    PayPeriod payperiod;
    EmploymentType employmentType;


    payperiod.setId(QString::number(getPayPeriod()));
    employmentType.setId(QString::number(getEmploymentType()));

    paytype.setId(getId());
    paytype.setPay_period(payperiod);
    paytype.setEmployment_type(employmentType);


    PaytypeMapper mapper;

    try {

        mapper.insert(paytype);

    } catch (std::exception &e) {
        Q_UNUSED(e);
        try {
            mapper.update(paytype);

        } catch (std::exception &e) {
            qInfo() << e.what() << "Could not save PaytypeFacade";
        }
    }
}

int PaytypeFacade::getPayPeriod() const
{
    return payPeriod;
}

void PaytypeFacade::setPayPeriod(int value)
{
    payPeriod = value;
    emit payPeriodChanged(value);
}

int PaytypeFacade::getEmploymentType() const
{
    return employmentType;
}

void PaytypeFacade::setEmploymentType(int value)
{
    employmentType = value;
    emit employmentTypeChanged(value);
}
