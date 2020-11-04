#ifndef SALARYFACADE_H
#define SALARYFACADE_H

#include "person.h"
#include "salary.h"
#include "money.h"
#include "salarydomainobject.h"

class SalaryFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Money gross_salary READ getGross_salary WRITE setGross_salary NOTIFY grossSalaryChanged)
    Q_PROPERTY(DateTime from_date READ getFrom_date WRITE setFrom_date NOTIFY fromDateChanged)
    Q_PROPERTY(DateTime to_date READ getTo_date WRITE setTo_date NOTIFY toDateChanged)

    Q_PROPERTY(Money net_salary READ getNet_salary NOTIFY netSalaryChanged)
    Q_PROPERTY(Money employee_nis READ getEmployee_nis NOTIFY employeeNisChanged)
    Q_PROPERTY(Money employer_nis READ getEmployer_nis NOTIFY employerNisChanged)
    Q_PROPERTY(Money paye READ getPaye  NOTIFY payeChanged)
    Q_PROPERTY(Money health_surcharge READ getHealth_surcharge NOTIFY healthSurchargeChanged)

public:
    explicit SalaryFacade(QObject *parent = nullptr);

    Money getGross_salary() const;
    void setGross_salary(Money value);

    Money getNet_salary() const;
    void setNet_salary(Money value);

    Money getPaye() const;
    void setPaye(Money value);

    Money getHealth_surcharge() const;
    void setHealth_surcharge(Money value);

    DateTime getFrom_date() const;
    void setFrom_date(const DateTime value);

    DateTime getTo_date() const;
    void setTo_date(const DateTime value);

    Money getEmployer_nis() const;
    void setEmployer_nis(const Money value);

    Money getEmployee_nis() const;
    void setEmployee_nis(const Money value);

public slots:
    bool pay(Employee employee);
    bool pay(QJsonObject employee);
    SalaryDomainObject findLastSalaryForEmployee(QJsonObject employee);

signals:
    void grossSalaryChanged(Money gross_salary);
    void netSalaryChanged(Money net_salary);
    void employeeNisChanged(Money employee_nis);
    void employerNisChanged(Money employer_nis);
    void payeChanged(Money paye);
    void healthSurchargeChanged(Money health_surcharge);
    void fromDateChanged(DateTime from_date);
    void toDateChanged(DateTime to_date);
    void salaryChanged(Salary s);

    void error(QString message);

private:
    Money gross_salary = 0;
    Money net_salary = 0;
    Money employee_nis = 0;
    Money employer_nis = 0;
    Money paye = 0;
    Money health_surcharge = 0;
    DateTime from_date,to_date;
    Salary salary;
    void setSalary();

};

#endif // SALARYFACADE_H
