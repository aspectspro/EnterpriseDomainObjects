#ifndef PAYTYPEDOMAINOBJECT_H
#define PAYTYPEDOMAINOBJECT_H
#include "AbstractObjects.h"

class PaytypeDomainObject : public AbstractDomainObject, public DomainCloneTemplate<PaytypeDomainObject>{

    Q_GADGET
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString pay_period READ getPay_period WRITE setPay_period)
    Q_PROPERTY(QString employment_type READ getEmployment_type WRITE setEmployment_type)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    QString getId() const;
    void setId(const QString &value);

    QString getPay_period() const;
    void setPay_period(const QString &value);

    QString getEmployment_type() const;
    void setEmployment_type(const QString &value);

private:
    QString id, pay_period, employment_type;
};

Q_DECLARE_METATYPE(PaytypeDomainObject)

class PaytypeMapper : public TemplateMapper<PaytypeDomainObject>{

    // AbstractMapper interface
public:
    virtual QString tableName() const override;
};

#endif // PAYTYPEDOMAINOBJECT_H
