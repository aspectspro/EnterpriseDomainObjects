#include "salarydomainobject.h"
#include "person.h"

SalaryDomainMapper SalaryYearToDate::mapper;

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

SalaryDomainObject::SalaryDomainObject(QJSValue json)
{
    this->fromJson(json.toVariant().toJsonObject());
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

SalaryDomainObject SalaryDomainObject::fromJs(QJsonValue json)
{
    SalaryDomainObject obj;
    obj.fromJson(json.toObject());
    return obj;
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


SalaryYearToDate::SalaryYearToDate()
{
    QDate dt = QDate::currentDate();
    setCurrentYear(dt.year());

    connect(this,&SalaryYearToDate::salary_idChanged,[=](QString salary_id){
        Q_UNUSED(salary_id);
        loadYearToDate();
    });

    connect(this,&SalaryYearToDate::salaryChanged,[=](){
        loadYearToDate();
    });
}

qint64 SalaryYearToDate::getCurrentYear() const
{
    return currentYear;
}

void SalaryYearToDate::setCurrentYear(qint64 value)
{
    currentYear = value;
}


Money SalaryYearToDate::getYearGross() const
{
    return yearGross;
}

void SalaryYearToDate::setYearGross(const Money value)
{
    yearGross = value;
    emit yearGrossChanged(value);
}

Money SalaryYearToDate::getYearNet() const
{
    return yearNet;
}

void SalaryYearToDate::setYearNet(const Money value)
{
    yearNet = value;
    emit yearNetChanged(value);
}

Money SalaryYearToDate::getYearNis() const
{
    return yearNis;
}

void SalaryYearToDate::setYearNis(const Money value)
{
    yearNis = value;
    emit yearNisChanged(value);
}

Money SalaryYearToDate::getYearHealthSurcharge() const
{
    return yearHealthSurcharge;
}

void SalaryYearToDate::setYearHealthSurcharge(const Money value)
{
    yearHealthSurcharge = value;
    emit yearHealthSurchargeChanged(value);
}

Money SalaryYearToDate::getYearPaye() const
{
    return yearPaye;
}

void SalaryYearToDate::setYearPaye(const Money value)
{
    yearPaye = value;
    emit yearPayeChanged(value);
}

void SalaryYearToDate::loadYearToDate()
{
    QString lastPaid,employeeId;

    try {
        auto loadedSalary = mapper.find(getSalary_id());
        lastPaid = loadedSalary.getDate_paid().toIsoDate();
        employeeId = loadedSalary.getEmployee_id();

    } catch (std::exception &e) {
        Q_UNUSED(e);
        lastPaid = getSalary().getDate_paid().toIsoDate();
        employeeId = getSalary().getEmployee_id();
    }

    auto currentYear = getCurrentYear();
    QString yearlyDateFormat = "yyyy-MM-dd,hh:mm:ss a";

    QDateTime startDate;
    startDate = startDate.fromString(QString("%1-%2-%3,12:00:00 am")
                                     .arg(currentYear)
                                     .arg("01")
                                     .arg("01"),yearlyDateFormat);

    QDateTime endDate;    

    endDate = endDate.fromString(QString("%1,11:59:59 pm")
                                 .arg(lastPaid),yearlyDateFormat);

    auto startTimestamp = startDate.toSecsSinceEpoch();
    auto endTimestamp = endDate.toSecsSinceEpoch();    

    try {
        auto all = mapper.loadAll(QString("employee_id='%1' AND date_paid >= %2 AND date_paid <= %3")
                                  .arg(employeeId)
                                  .arg(startTimestamp)
                                  .arg(endTimestamp));

        qint64 _gross = 0, _net = 0, _nis = 0,
            _paye = 0 , _hsc = 0;

        foreach (auto _salary, all) {
            _gross += _salary.getGross_pay().asInt();
            _net += _salary.getNet_pay().asInt();
            _nis += _salary.getEmployee_nis().asInt();
            _paye += _salary.getPaye().asInt();
            _hsc += _salary.getHealth_surcharge().asInt();
        }

        setYearGross(_gross);
        setYearNet(_net);
        setYearNis(_nis);
        setYearPaye(_paye);
        setYearHealthSurcharge(_hsc);

    } catch (std::exception &e) {
        Q_UNUSED(e);
        qInfo() << QString("No Salary for '%1' as yet.").arg(currentYear);
    }

}

SalaryDomainObject SalaryYearToDate::getSalary() const
{
    return salary;
}

void SalaryYearToDate::setSalary(const SalaryDomainObject value)
{
    salary = value;
    emit salaryChanged(value);
}

QString SalaryYearToDate::getSalary_id() const
{
    return salary_id;
}

void SalaryYearToDate::setSalary_id(const QString &value)
{
    salary_id = value;
    emit salary_idChanged(value);
}
