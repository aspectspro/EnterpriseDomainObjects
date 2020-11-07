#ifndef PAYRATEDOMAINOBJECT_H
#define PAYRATEDOMAINOBJECT_H
#include <AbstractObjects.h>
#include "money.h"

class PayrateDomainObject : public AbstractDomainObject, public DomainCloneTemplate<PayrateDomainObject>
{
    Q_GADGET
    Q_PROPERTY(QString employee_id READ getEmployee_id WRITE setEmployee_id)
    Q_PROPERTY(Money payrate READ getPayrate WRITE setPayrate)
    Q_PROPERTY(Money overtime_one READ getOvertime_one WRITE setOvertime_one)
    Q_PROPERTY(Money overtime_two READ getOvertime_two WRITE setOvertime_two)
    Q_PROPERTY(Money overtime_three READ getOvertime_three WRITE setOvertime_three)

public:
    PayrateDomainObject();

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    Money getPayrate() const;
    void setPayrate(const Money &value);

    Money getOvertime_one() const;
    void setOvertime_one(const Money &value);

    Money getOvertime_two() const;
    void setOvertime_two(const Money &value);

    Money getOvertime_three() const;
    void setOvertime_three(const Money &value);

    QString getEmployee_id() const;
    void setEmployee_id(const QString &value);

private:
    QString employee_id;
    Money payrate;
    Money overtime_one, overtime_two, overtime_three;
};

Q_DECLARE_METATYPE(PayrateDomainObject)

class PayrateMapper : public TemplateMapper<PayrateDomainObject>{

    // AbstractMapper interface
public:
    virtual QString tableName() const override;

};

#endif // PAYRATEDOMAINOBJECT_H
