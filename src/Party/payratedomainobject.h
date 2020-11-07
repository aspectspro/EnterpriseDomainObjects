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

class PayrateFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString employee_id READ getEmployee_id WRITE setEmployee_id NOTIFY employee_idChanged)
    Q_PROPERTY(Money overtime_one READ getOvertime_one WRITE setOvertime_one NOTIFY overtime_oneChanged)
    Q_PROPERTY(Money overtime_two READ getOvertime_two WRITE setOvertime_two NOTIFY overtime_twoChanged)
    Q_PROPERTY(Money overtime_three READ getOvertime_three WRITE setOvertime_three NOTIFY overtime_threeChanged)

public:
    PayrateFacade();
    virtual ~PayrateFacade() {}

    QString getEmployee_id() const;
    void setEmployee_id(const QString &value);

    Money getPayrate() const;
    void setPayrate(const Money &value);

    Money getOvertime_one() const;
    void setOvertime_one(const Money &value);

    Money getOvertime_two() const;
    void setOvertime_two(const Money &value);

    Money getOvertime_three() const;
    void setOvertime_three(const Money &value);

public slots:
    void save();
    void load();

signals:
    void employee_idChanged(QString employee_id);
    void payrateChanged(Money payrate);
    void overtime_oneChanged(Money overtime_one);
    void overtime_twoChanged(Money overtime_two);
    void overtime_threeChanged(Money overtime_three);

private:
    QString employee_id;
    Money payrate, overtime_one, overtime_two, overtime_three;
    static PayrateMapper mapper;
};

#endif // PAYRATEDOMAINOBJECT_H
