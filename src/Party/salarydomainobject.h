#ifndef SALARYDOMAINOBJECT_H
#define SALARYDOMAINOBJECT_H
#include "AbstractObjects.h"
#include "datetime.h"
#include "money.h"

class SalaryDomainObject : public AbstractDomainObject
{
    Q_GADGET
public:
    SalaryDomainObject();
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

#endif // SALARYDOMAINOBJECT_H
