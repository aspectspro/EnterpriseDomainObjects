#ifndef SALARYFACADE_H
#define SALARYFACADE_H

#include "salary.h"
#include "money.h"

class SalaryFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int gross_salary READ getGross_salary WRITE setGross_salary NOTIFY grossSalaryChanged)
    Q_PROPERTY(QString from_date READ getFrom_date WRITE setFrom_date NOTIFY fromDateChanged)
    Q_PROPERTY(QString to_date READ getTo_date WRITE setTo_date NOTIFY toDateChanged)

    Q_PROPERTY(int net_salary READ getNet_salary NOTIFY netSalaryChanged)
    Q_PROPERTY(int nis READ getNis NOTIFY nisChanged)
    Q_PROPERTY(int paye READ getPaye  NOTIFY payeChanged)
    Q_PROPERTY(int health_surcharge READ getHealth_surcharge NOTIFY healthSurchargeChanged)

public:
    explicit SalaryFacade(QObject *parent = nullptr);

    int getGross_salary() const;
    void setGross_salary(int value);

    int getNet_salary() const;
    void setNet_salary(int value);

    int getNis() const;
    void setNis(int value);

    int getPaye() const;
    void setPaye(int value);

    int getHealth_surcharge() const;
    void setHealth_surcharge(int value);

    QString getFrom_date() const;
    void setFrom_date(const QString value);

    QString getTo_date() const;
    void setTo_date(const QString value);

public slots:

signals:
    void grossSalaryChanged(int gross_salary);
    void netSalaryChanged(int net_salary);
    void nisChanged(int nis);
    void payeChanged(int paye);
    void healthSurchargeChanged(int health_surcharge);
    void fromDateChanged(QString from_date);
    void toDateChanged(QString to_date);

    void salaryChanged(Salary s);

private:
    int gross_salary = 0;
    int net_salary = 0;
    int nis = 0;
    int paye = 0;
    int health_surcharge = 0;
    QString from_date,to_date;
    Salary salary;

    void setSalary();

};

#endif // SALARYFACADE_H
