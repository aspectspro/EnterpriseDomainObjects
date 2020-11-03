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
        auto _nis = NisCalculator::getNisForSalary(s);
        setNis(_nis);

        auto _paye = PayeCalculator::getPayeForSalary(s);
        setPaye(_paye);

        auto _healthSurcharge = HealthSurchargeCalculator::getHealthSurcharge(s);
        setHealth_surcharge(_healthSurcharge);

        auto taxes = _nis+_paye+_healthSurcharge;
        setNet_salary(gross_salary-taxes);

    });

    setFrom_date(QDate::currentDate().toString(Qt::ISODate));
    setTo_date(QDate::currentDate().toString(Qt::ISODate));

}

int SalaryFacade::getGross_salary() const
{
    return gross_salary;
}

void SalaryFacade::setGross_salary(int value)
{
    gross_salary = value;
    emit grossSalaryChanged(value);
}

int SalaryFacade::getNet_salary() const
{
    return net_salary;
}

void SalaryFacade::setNet_salary(int value)
{
    net_salary = value;
    emit netSalaryChanged(value);
}

int SalaryFacade::getNis() const
{
    return nis;
}

void SalaryFacade::setNis(int value)
{
    nis = value;
    emit nisChanged(value);
}

int SalaryFacade::getPaye() const
{
    return paye;
}

void SalaryFacade::setPaye(int value)
{
    paye = value;
    emit payeChanged(value);
}

int SalaryFacade::getHealth_surcharge() const
{
    return health_surcharge;
}

void SalaryFacade::setHealth_surcharge(int value)
{
    health_surcharge = value;
    emit healthSurchargeChanged(value);
}

QString SalaryFacade::getFrom_date() const
{
    return from_date;
}

void SalaryFacade::setFrom_date(const QString value)
{
    from_date = value;
    emit fromDateChanged(value);
}

QString SalaryFacade::getTo_date() const
{
    return to_date;
}

void SalaryFacade::setTo_date(const QString value)
{
    to_date = value;
    emit toDateChanged(value);
}

void SalaryFacade::setSalary()
{
    Salary s({from_date,to_date});
    s.setAmount(gross_salary);
    this->salary = s;
    emit salaryChanged(s);
}
