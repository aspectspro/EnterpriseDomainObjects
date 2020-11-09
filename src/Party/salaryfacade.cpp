#include "salaryfacade.h"

DomainModelPtr SalaryFacade::employeeSalaries = ModelFactory::createModel<SalaryDomainObject>();

SalaryDomainMapper SalaryFacade::mapper;

SalaryFacade::SalaryFacade(QObject *parent) : QObject(parent)
{    

    connect(this,&SalaryFacade::idChanged,[=](){
        load();
    });

    connect(this,&SalaryFacade::fromDateChanged,[=](){
        this->setSalary();
    });

    connect(this,&SalaryFacade::toDateChanged,[=](){
        this->setSalary();
    });

    connect(this,&SalaryFacade::grossSalaryChanged,[=](){
        this->setSalary();
    });

    connect(this,&SalaryFacade::salaryChanged,[=](Salary s){

        NisCalculator calc(s);
        auto _nis = calc.getEmployeeContribution();
        setEmployee_nis(_nis);
        setEmployer_nis(calc.getEmployerContribution());

        auto _paye = PayeCalculator::getPayeForSalary(s);
        setPaye(_paye);

        auto _healthSurcharge = HealthSurchargeCalculator::getHealthSurcharge(s);
        setHealth_surcharge(_healthSurcharge);

        auto taxes = _nis+_paye+_healthSurcharge;
        setNet_salary(gross_salary-taxes);

    });

    setFrom_date(DateTime::getNow());
    setTo_date(DateTime::getNow());

}

Money SalaryFacade::getGross_salary() const
{
    return gross_salary;
}

void SalaryFacade::setGross_salary(Money value)
{
    gross_salary = value;
    emit grossSalaryChanged(value);
}

Money SalaryFacade::getNet_salary() const
{
    return net_salary;
}

void SalaryFacade::setNet_salary(Money value)
{
    net_salary = value;
    emit netSalaryChanged(value);
}

Money SalaryFacade::getPaye() const
{
    return paye;
}

void SalaryFacade::setPaye(Money value)
{
    paye = value;
    emit payeChanged(value);
}

Money SalaryFacade::getHealth_surcharge() const
{
    return health_surcharge;
}

void SalaryFacade::setHealth_surcharge(Money value)
{
    health_surcharge = value;
    emit healthSurchargeChanged(value);
}

DateTime SalaryFacade::getFrom_date() const
{
    return from_date;
}

void SalaryFacade::setFrom_date(const DateTime value)
{
    from_date = value;
    emit fromDateChanged(value);
}

DateTime SalaryFacade::getTo_date() const
{
    return to_date;
}

void SalaryFacade::setTo_date(const DateTime value)
{
    to_date = value;
    emit toDateChanged(value);
}

bool SalaryFacade::pay(Employee employee)
{
    SalaryDomainMapper mapper;
    SalaryDomainObject salaryObject;

    salaryObject.generateId();
    salaryObject.setEmployee_id(employee.getId());
    salaryObject.setGross_pay(this->gross_salary);
    salaryObject.setNet_pay(this->net_salary);
    salaryObject.setPaye(this->paye);
    salaryObject.setEmployee_nis(this->getEmployee_nis());
    salaryObject.setEmployer_nis(this->getEmployer_nis());
    salaryObject.setHealth_surcharge(this->health_surcharge);
    salaryObject.setDate_from(this->from_date);
    salaryObject.setDate_to(this->to_date);
    salaryObject.setDate_paid(DateTime::getNow());

    try {
        mapper.insert(salaryObject);
    } catch (std::exception &e) {
        emit error(e.what());
        qInfo() << e.what();
        return false;
    }
    return true;
}

bool SalaryFacade::pay(QJsonObject employee)
{
    Employee e;
    e.fromJson(employee);
    return pay(e);
}

SalaryDomainObject SalaryFacade::findLastSalaryForEmployee(QJsonObject employee)
{
    SalaryDomainMapper mapper;
    Employee e;
    e.fromJson(employee);

    SalaryDomainObject salary;

    try {
        salary = mapper.loadAll(QString("employee_id='%1' ORDER BY date_paid DESC").arg(e.getId())).first();
    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << "Employee hasn't been paid as yet.";
    }

    return salary;
}

SalaryDomainObject SalaryFacade::findLastSalaryForEmployee()
{
    SalaryDomainObject salary;

    try {
        salary = mapper.loadAll(QString("employee_id='%1' ORDER BY date_paid DESC").arg(getEmployee_id())).first();
    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << "Employee hasn't been paid as yet.";
    }

    return salary;

}

void SalaryFacade::loadSalaries(QJsonObject employee)
{
    Employee _employee;
    _employee.fromJson(employee);

    SalaryDomainMapper mapper;
    DomainObjectListPtr salaries = std::make_shared<QList<DomainObjectPtr>>();
    salaries->clear();

    try {
        auto loadedSalaries = mapper.loadAll(QString("employee_id='%1'").arg(_employee.getId()));
        foreach (auto salary, loadedSalaries) {
            salaries->append(salary.clone());
        }

    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << QString("No Salaries available for '%1 %2'").arg(_employee.getFirst_name())
                   .arg(_employee.getLast_name());
    }


    employeeSalaries->changeDomainList(salaries);
    emit employeeSalariesChanged(employeeSalaries.get());
}

QAbstractItemModel *SalaryFacade::getEmployeeSalaries()
{
    return employeeSalaries.get();
}

void SalaryFacade::load()
{
    try {
        auto salary = mapper.find(getId());
        setPaye(salary.getPaye());
        setDate_paid(salary.getDate_paid());
        setTo_date(salary.getDate_to());
        setFrom_date(salary.getDate_from());
        setNet_salary(salary.getNet_pay());
        setEmployee_id(salary.getEmployee_id());
        setEmployee_nis(salary.getEmployee_nis());
        setEmployer_nis(salary.getEmployer_nis());
        setGross_salary(salary.getGross_pay());
        setHealth_surcharge(salary.getHealth_surcharge());

    } catch (std::exception &e) {
        qInfo() << e.what() << QString("Couldn't load Salary '%1'").arg(getId());
    }


}

void SalaryFacade::save()
{
    SalaryDomainObject salaryObject;

    salaryObject.generateId();
    salaryObject.setEmployee_id(getEmployee_id());
    salaryObject.setGross_pay(getGross_salary());
    salaryObject.setNet_pay(getNet_salary());
    salaryObject.setPaye(getPaye());
    salaryObject.setEmployee_nis(getEmployee_nis());
    salaryObject.setEmployer_nis(getEmployer_nis());
    salaryObject.setHealth_surcharge(getHealth_surcharge());
    salaryObject.setDate_from(getFrom_date());
    salaryObject.setDate_to(getTo_date());
    salaryObject.setDate_paid(DateTime::getNow());

    try {
        mapper.insert(salaryObject);
        id = salaryObject.getId();
        emit saved(getId());

    } catch (std::exception &e) {
        emit error(e.what());
        qInfo() << e.what();
    }

}

DateTime SalaryFacade::getDate_paid() const
{
    return date_paid;
}

void SalaryFacade::setDate_paid(const DateTime &value)
{
    date_paid = value;
    emit date_paidChanged(value);
}

Money SalaryFacade::getEmployee_nis() const
{
    return employee_nis;
}

void SalaryFacade::setEmployee_nis(const Money value)
{
    employee_nis = value;
    emit employeeNisChanged(value);
}

Money SalaryFacade::getEmployer_nis() const
{
    return employer_nis;
}

void SalaryFacade::setEmployer_nis(const Money value)
{
    employer_nis = value;
    emit employerNisChanged(value);
}

void SalaryFacade::setSalary()
{
    Salary s({getFrom_date().toIsoDate(),getTo_date().toIsoDate()});
    s.setAmount(getGross_salary());
    this->salary = s;
    emit salaryChanged(s);
}

QString SalaryFacade::getId() const
{
    return id;
}

void SalaryFacade::setId(const QString &value)
{
    id = value;
    emit idChanged(value);
}

QString SalaryFacade::getEmployee_id() const
{
    return employee_id;
}

void SalaryFacade::setEmployee_id(const QString &value)
{
    employee_id = value;
    emit employee_idChanged(value);
}
