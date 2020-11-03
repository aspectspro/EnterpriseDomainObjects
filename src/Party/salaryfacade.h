#ifndef SALARYFACADE_H
#define SALARYFACADE_H

#include "salary.h"
#include "money.h"

class SalaryFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Money gross_salary READ getGross_salary WRITE setGross_salary NOTIFY grossSalaryChanged)
    Q_PROPERTY(QString from_date READ getFrom_date WRITE setFrom_date NOTIFY fromDateChanged)
    Q_PROPERTY(QString to_date READ getTo_date WRITE setTo_date NOTIFY toDateChanged)

    Q_PROPERTY(Money net_salary READ getNet_salary NOTIFY netSalaryChanged)
    Q_PROPERTY(Money nis READ getNis NOTIFY nisChanged)
    Q_PROPERTY(Money paye READ getPaye  NOTIFY payeChanged)
    Q_PROPERTY(Money health_surcharge READ getHealth_surcharge NOTIFY healthSurchargeChanged)

public:
    explicit SalaryFacade(QObject *parent = nullptr);

    Money getGross_salary() const;
    void setGross_salary(Money value);

    Money getNet_salary() const;
    void setNet_salary(Money value);

    Money getNis() const;
    void setNis(Money value);

    Money getPaye() const;
    void setPaye(Money value);

    Money getHealth_surcharge() const;
    void setHealth_surcharge(Money value);

    QString getFrom_date() const;
    void setFrom_date(const QString value);

    QString getTo_date() const;
    void setTo_date(const QString value);

public slots:

signals:
    void grossSalaryChanged(Money gross_salary);
    void netSalaryChanged(Money net_salary);
    void nisChanged(Money nis);
    void payeChanged(Money paye);
    void healthSurchargeChanged(Money health_surcharge);
    void fromDateChanged(QString from_date);
    void toDateChanged(QString to_date);

    void salaryChanged(Salary s);

private:
    Money gross_salary = 0;
    Money net_salary = 0;
    Money nis = 0;
    Money paye = 0;
    Money health_surcharge = 0;
    QString from_date,to_date;
    Salary salary;

    void setSalary();

};

#endif // SALARYFACADE_H
