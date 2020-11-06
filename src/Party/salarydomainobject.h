#ifndef SALARYDOMAINOBJECT_H
#define SALARYDOMAINOBJECT_H
#include "AbstractObjects.h"
#include "datetime.h"
#include "money.h"
#include <QtQml/QJSValue>

class SalaryDomainObject : public AbstractDomainObject, public DomainCloneTemplate<SalaryDomainObject>
{
    Q_GADGET
public:
    SalaryDomainObject();
    SalaryDomainObject(QJSValue json);
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString employee_id READ getEmployee_id WRITE setEmployee_id)
    Q_PROPERTY(Money gross_pay READ getGross_pay WRITE setGross_pay)
    Q_PROPERTY(Money net_pay READ getNet_pay WRITE setNet_pay)
    Q_PROPERTY(Money employee_nis READ getEmployee_nis WRITE setEmployee_nis)
    Q_PROPERTY(Money employer_nis READ getEmployer_nis WRITE setEmployer_nis)
    Q_PROPERTY(Money paye READ getPaye WRITE setPaye)
    Q_PROPERTY(Money health_surcharge READ getHealth_surcharge WRITE setHealth_surcharge)
    Q_PROPERTY(DateTime date_from READ getDate_from WRITE setDate_from)
    Q_PROPERTY(DateTime date_to READ getDate_to WRITE setDate_to)
    Q_PROPERTY(DateTime date_paid READ getDate_paid WRITE setDate_paid)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
    virtual void registerConverter() override;

    QString getId() const;
    void setId(const QString &value);

    QString getEmployee_id() const;
    void setEmployee_id(const QString &value);

    Money getGross_pay() const;
    void setGross_pay(const Money &value);

    Money getNet_pay() const;
    void setNet_pay(const Money &value);

    Money getEmployee_nis() const;
    void setEmployee_nis(const Money &value);

    Money getEmployer_nis() const;
    void setEmployer_nis(const Money &value);

    Money getPaye() const;
    void setPaye(const Money &value);

    Money getHealth_surcharge() const;
    void setHealth_surcharge(const Money &value);


    DateTime getDate_from() const;
    void setDate_from(const DateTime &value);

    DateTime getDate_to() const;
    void setDate_to(const DateTime &value);

    DateTime getDate_paid() const;
    void setDate_paid(const DateTime &value);

    Q_INVOKABLE static SalaryDomainObject fromJs(QJsonValue json);

private:
    QString id,employee_id;
    Money gross_pay,net_pay,employee_nis,employer_nis,
    paye,health_surcharge;
    DateTime date_from,date_to,date_paid;
};

class SalaryDomainMapper : public TemplateMapper<SalaryDomainObject>{

    // AbstractMapper interface
public:
    virtual QString tableName() const override;

    // AbstractMapper interface
protected:
    virtual void injectInsert(AbstractDomainObject &domainObject) const override;
};

class SalaryYearToDate : public QObject{

    Q_OBJECT
    // AbstractDomainObject interface

    Q_PROPERTY(Money yearGross READ getYearGross NOTIFY yearGrossChanged)
    Q_PROPERTY(Money yearNet READ getYearNet NOTIFY yearNetChanged)
    Q_PROPERTY(Money yearNis READ getYearNis NOTIFY yearNisChanged)
    Q_PROPERTY(Money yearHealthSurcharge READ getYearHealthSurcharge NOTIFY yearHealthSurchargeChanged)
    Q_PROPERTY(Money yearPaye READ getYearPaye NOTIFY yearPayeChanged)
    Q_PROPERTY(SalaryDomainObject salary READ getSalary WRITE setSalary NOTIFY salaryChanged)

public:
    SalaryYearToDate();

    int getCurrentYear() const;
    void setCurrentYear(int value);

    Money getYearGross() const;
    void setYearGross(const Money value);

    Money getYearNet() const;
    void setYearNet(const Money value);

    Money getYearNis() const;
    void setYearNis(const Money value);

    Money getYearHealthSurcharge() const;
    void setYearHealthSurcharge(const Money value);

    Money getYearPaye() const;
    void setYearPaye(const Money value);

    Q_INVOKABLE void loadYearToDate();

    SalaryDomainObject getSalary() const;
    void setSalary(const SalaryDomainObject value);

signals:
    void employeeIdChanged(QString employeeId);
    void yearGrossChanged(Money yearGross);
    void yearNetChanged(Money yearNet);
    void yearNisChanged(Money yearNis);
    void yearHealthSurchargeChanged(Money yearHealthSurcharge);
    void yearPayeChanged(Money yearPaye);
    void lastPaidChanged(QString lastPaid);
    void salaryChanged(SalaryDomainObject salary);

private:
    int currentYear;
    Money yearGross;
    Money yearNet;
    Money yearNis;
    Money yearHealthSurcharge;
    Money yearPaye;
    SalaryDomainObject salary;
};

#endif // SALARYDOMAINOBJECT_H
