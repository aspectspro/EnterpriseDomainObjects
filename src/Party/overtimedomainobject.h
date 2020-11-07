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

struct AbstractFacade : public QObject{
    Q_OBJECT

signals:
    void error(QString message);

public slots:
    virtual void save(){}
    virtual void load(){}


};

class OvertimeFacade : public AbstractFacade
{
    Q_OBJECT
    Q_PROPERTY(Double overtime_rate_one READ getOvertime_rate_one WRITE setOvertime_rate_one NOTIFY overtime_rate_oneChanged)
    Q_PROPERTY(Double overtime_rate_two READ getOvertime_rate_two WRITE setOvertime_rate_two NOTIFY overtime_rate_twoChanged)
    Q_PROPERTY(Double overtime_rate_three READ getOvertime_rate_three WRITE setOvertime_rate_three NOTIFY overtime_rate_threeChanged)

public:
    OvertimeFacade();
    virtual ~OvertimeFacade() {}

    Double getOvertime_rate_one() const;
    void setOvertime_rate_one(const Double value);

    Double getOvertime_rate_two() const;
    void setOvertime_rate_two(const Double value);

    Double getOvertime_rate_three() const;
    void setOvertime_rate_three(const Double value);

signals:
    void overtime_rate_oneChanged(Double overtime_rate_one);
    void overtime_rate_twoChanged(Double overtime_rate_two);
    void overtime_rate_threeChanged(Double overtime_rate_three);

private:
    Double overtime_rate_one = 0;
    Double overtime_rate_two = 0;
    Double overtime_rate_three = 0;
    OvertimeMapper mapper;

    // AbstractFacade interface
public slots:
    virtual void save() override;
    virtual void load() override;
};



#endif // OVERTIMEDOMAINOBJECT_H
