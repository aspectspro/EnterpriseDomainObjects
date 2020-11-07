#ifndef OVERTIMEDOMAINOBJECT_H
#define OVERTIMEDOMAINOBJECT_H
#include "AbstractObjects.h"
#include "money.h"
#include "double.h"

struct OvertimeDomainObject : public AbstractDomainObject, public DomainCloneTemplate<OvertimeDomainObject>
{
    Q_GADGET
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(double overtime_rate_one READ getOvertime_rate_one WRITE setOvertime_rate_one)
    Q_PROPERTY(double overtime_rate_two READ getOvertime_rate_two WRITE setOvertime_rate_two)
    Q_PROPERTY(double overtime_rate_three READ getOvertime_rate_three WRITE setOvertime_rate_three)

public:
    OvertimeDomainObject();

    QString getId() const;
    void setId(const QString &value);

    double getOvertime_rate_one() const;
    void setOvertime_rate_one(double value);

    double getOvertime_rate_two() const;
    void setOvertime_rate_two(double value);

    double getOvertime_rate_three() const;
    void setOvertime_rate_three(const double value);

private:
    QString id;
    double overtime_rate_one = 0;
    double overtime_rate_two = 0;
    double overtime_rate_three = 0;

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

class OvertimeFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double overtime_rate_one READ getOvertime_rate_one WRITE setOvertime_rate_one NOTIFY overtime_rate_oneChanged)
    Q_PROPERTY(double overtime_rate_two READ getOvertime_rate_two WRITE setOvertime_rate_two NOTIFY overtime_rate_twoChanged)
    Q_PROPERTY(double overtime_rate_three READ getOvertime_rate_three WRITE setOvertime_rate_three NOTIFY overtime_rate_threeChanged)

public:
    OvertimeFacade();
    virtual ~OvertimeFacade() {}

    double getOvertime_rate_one() const;
    void setOvertime_rate_one(const double value);

    double getOvertime_rate_two() const;
    void setOvertime_rate_two(const double value);

    double getOvertime_rate_three() const;
    void setOvertime_rate_three(const double value);

signals:
    void overtime_rate_oneChanged(double overtime_rate_one);
    void overtime_rate_twoChanged(double overtime_rate_two);
    void overtime_rate_threeChanged(double overtime_rate_three);

private:
    double overtime_rate_one = 0;
    double overtime_rate_two = 0;
    double overtime_rate_three = 0;
    OvertimeMapper mapper;

    // AbstractFacade interface
public slots:
    virtual void save();
    virtual void load();
};



#endif // OVERTIMEDOMAINOBJECT_H
