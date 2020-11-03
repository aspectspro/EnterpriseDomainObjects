#include "salaryfacade.h"

SalaryFacade::SalaryFacade(QObject *parent) : QObject(parent)
{    

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

void SalaryFacade::pay(Employee e)
{
    SalaryDomainMapper mapper;
    SalaryDomainObject salaryObject;

    salaryObject.generateId();
    salaryObject.setEmployee_id(e.getId());
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
    }
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
    Salary s({from_date.toIsoDate(),to_date.toIsoDate()});
    s.setAmount(gross_salary);
    this->salary = s;
    emit salaryChanged(s);
}
