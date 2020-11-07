#ifndef OVERTIMEDOMAINOBJECT_H
#define OVERTIMEDOMAINOBJECT_H
#include "AbstractObjects.h"
#include "money.h"
#include "double.h"

struct OvertimeDomainObject : public AbstractDomainObject, public DomainCloneTemplate<OvertimeDomainObject>
{
    Q_GADGET
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(Double overtime_rate_one READ getOvertime_rate_one WRITE setOvertime_rate_one)
    Q_PROPERTY(Double overtime_rate_two READ getOvertime_rate_two WRITE setOvertime_rate_two)
    Q_PROPERTY(Double overtime_rate_three READ getOvertime_rate_three WRITE setOvertime_rate_three)

public:
    OvertimeDomainObject();

    QString getId() const;
    void setId(const QString &value);

    Double getOvertime_rate_one() const;
    void setOvertime_rate_one(Double value);

    Double getOvertime_rate_two() const;
    void setOvertime_rate_two(Double value);

    Double getOvertime_rate_three() const;
    void setOvertime_rate_three(const Double value);

private:
    QString id;
    Double overtime_rate_one = 0;
    Double overtime_rate_two = 0;
    Double overtime_rate_three = 0;

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
};

Q_DECLARE_METATYPE(OvertimeDomainObject)

class OvertimeMapper : public TemplateMapper<OvertimeDomainObject>{


    // AbstractMapper interface
public:
    virtual QString tableName() const override;
};



#endif // OVERTIMEDOMAINOBJECT_H
