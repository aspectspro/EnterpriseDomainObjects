#ifndef PAYTYPEDOMAINOBJECT_H
#define PAYTYPEDOMAINOBJECT_H
#include "AbstractObjects.h"

class EmploymentType : public AbstractDomainObject, public DomainCloneTemplate<EmploymentType>{

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
    Q_PROPERTY(QString employee_title READ getEmployee_title WRITE setEmployee_title)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    QString getId() const;
    void setId(const QString &value);

    PayPeriod getPay_period() const;
    void setPay_period(const PayPeriod &value);

    EmploymentType getEmployment_type() const;
    void setEmployment_type(const EmploymentType &value);

    QString getEmployee_title() const;
    void setEmployee_title(const QString &value);

private:
    QString id;
    QString employee_title;
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
    Q_PROPERTY(EmploymentTypeEnum _id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QAbstractItemModel* model READ getModel)


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
    static QAbstractItemModel *getModel();

signals:
    void idChanged(EmploymentTypeEnum id);
    void nameChanged(QString name);

private:
    EmploymentTypeEnum id = HOURLY;
    QString name;
    static EmploymentTypeMapper mapper;
    static DomainModelPtr employmentTypeModel;
};


class PayPeriodFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PayPeriodEnum _id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QAbstractItemModel *model READ getModel)

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
    static QAbstractItemModel *getModel();

signals:
    void idChanged(PayPeriodEnum id);
    void nameChanged(QString name);

private:
    PayPeriodEnum id = MONTHLY;
    QString name;
    static PayPeriodMapper mapper;
    static DomainModelPtr payPeriodModel;
};

class PaytypeFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(qint64 payPeriod READ getPayPeriod WRITE setPayPeriod NOTIFY payPeriodChanged)
    Q_PROPERTY(qint64 employmentType READ getEmploymentType WRITE setEmploymentType NOTIFY employmentTypeChanged)
    Q_PROPERTY(QString employee_title READ getEmployee_title WRITE setEmployee_title NOTIFY employee_titleChanged)

public:
    PaytypeFacade();

    virtual ~PaytypeFacade() {}

    QString getId() const;
    void setId(const QString &value);

    qint64 getPayPeriod() const;
    void setPayPeriod(qint64 value);

    qint64 getEmploymentType() const;
    void setEmploymentType(qint64 value);

    QString getEmployee_title() const;
    void setEmployee_title(const QString &value);

public slots:
    void load();
    void save();

signals:
    void idChanged(QString id);
    void payPeriodChanged(qint64 payPeriod);
    void employmentTypeChanged(qint64 employmentType);
    void employee_titleChanged(QString employee_title);
    void saved();

private:
    QString id;
    QString employee_title;
    qint64 payPeriod = PayPeriodFacade::MONTHLY;
    qint64 employmentType = EmploymentTypeFacade::HOURLY;
    static PaytypeMapper mapper;
};

#endif // PAYTYPEDOMAINOBJECT_H
