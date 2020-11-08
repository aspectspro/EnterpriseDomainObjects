#ifndef PAYTYPEDOMAINOBJECT_H
#define PAYTYPEDOMAINOBJECT_H
#include "AbstractObjects.h"

class EmploymentType : public AbstractDomainObject{

    Q_GADGET
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString name READ getName WRITE setName)


    // AbstractDomainObject interface
public:
    EmploymentType();
    virtual const QMetaObject &metaObject() const override;

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    bool operator==(const EmploymentType &empType);

private:
    QString id;
    QString name;

    // AbstractDomainObject interface
public:
    virtual void registerConverter() override;

};

Q_DECLARE_METATYPE(EmploymentType)


class EmploymentTypeMapper : public TemplateMapper<EmploymentType>{

    // AbstractMapper interface
public:
    virtual QString tableName() const override;
};

class PayPeriod : public AbstractDomainObject, public DomainCloneTemplate<PayPeriod>{

    Q_GADGET
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString name READ getName WRITE setName)

    // AbstractDomainObject interface
public:
    PayPeriod();
    virtual const QMetaObject &metaObject() const override;

    bool operator==(const PayPeriod &period);

    QString getId() const;
    void setId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

private:
    QString id;
    QString name;

    // AbstractDomainObject interface
public:
    virtual void registerConverter() override;

};

Q_DECLARE_METATYPE(PayPeriod)

class PayPeriodMapper : public TemplateMapper<PayPeriod>{

    // AbstractMapper interface
public:
    virtual QString tableName() const override;
};

class PaytypeDomainObject : public AbstractDomainObject, public DomainCloneTemplate<PaytypeDomainObject>{

    Q_GADGET
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(PayPeriod pay_period READ getPay_period WRITE setPay_period)
    Q_PROPERTY(EmploymentType employment_type READ getEmployment_type WRITE setEmployment_type)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    QString getId() const;
    void setId(const QString &value);

    PayPeriod getPay_period() const;
    void setPay_period(const PayPeriod &value);

    EmploymentType getEmployment_type() const;
    void setEmployment_type(const EmploymentType &value);

private:
    QString id;
    PayPeriod pay_period;
    EmploymentType employment_type;
};

Q_DECLARE_METATYPE(PaytypeDomainObject)

class PaytypeMapper : public TemplateMapper<PaytypeDomainObject>{

    // AbstractMapper interface
public:
    virtual QString tableName() const override;

    // AbstractMapper interface
protected:
    virtual void injectLoad(AbstractDomainObject &domainObject) const override;
};


class EmploymentTypeFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(EmploymentTypeEnum id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)


public:
    enum EmploymentTypeEnum{
        HOURLY = 0,
        SALARIED = 1,
        COMMISSIONED = 2
    };

    Q_ENUM(EmploymentTypeEnum)

    EmploymentTypeFacade();

    virtual ~EmploymentTypeFacade() {}

    QString getName() const;
    void setName(const QString &value);

    EmploymentTypeEnum getId() const;
    void setId(const EmploymentTypeFacade::EmploymentTypeEnum value);

    void load();

    static void initializeEmploymentTypes();

signals:
    void idChanged(EmploymentTypeEnum id);
    void nameChanged(QString name);

private:
    EmploymentTypeEnum id;
    QString name;
    static EmploymentTypeMapper mapper;
};


class PayPeriodFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PayPeriodEnum id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:

    enum PayPeriodEnum{
        DAILY,
        WEEKLY,
        FORTNIGHTLY,
        MONTHLY
    };

    Q_ENUM(PayPeriodEnum)

    PayPeriodFacade();

    virtual ~PayPeriodFacade() {}

    PayPeriodEnum getId() const;
    void setId(const PayPeriodFacade::PayPeriodEnum value);

    QString getName() const;
    void setName(const QString &value);

    void load();

    static void initializePayPeriod();

signals:
    void idChanged(PayPeriodEnum id);
    void nameChanged(QString name);

private:
    PayPeriodEnum id;
    QString name;
    static PayPeriodMapper mapper;

};

class PaytypeFacade : public QObject
{
    Q_OBJECT

    enum EmploymentType{
        HOURLY,
        SALARY,
        COMMISSION
    };

    enum PayPeriod{
        DAILY,
        WEEKLY,
        FORTNIGHTLY,
        MONTHLY
    };

public:
    PaytypeFacade() {}
    virtual ~PaytypeFacade() {}


private:

};

#endif // PAYTYPEDOMAINOBJECT_H
