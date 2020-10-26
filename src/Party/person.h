#ifndef PERSON_H
#define PERSON_H
#include "abstractparty.h"

class DateTime{

    Q_GADGET
public:
    DateTime();
    int getTimestamp() const;
    void setTimestamp(int value);
    QString getDateTimeAsString();
    static DateTime getNow();

private:
    int timestamp = 0;
    void registerMetaType();
};

Q_DECLARE_METATYPE(DateTime)

class Person : public AbstractParty, public DomainCloneTemplate<Person>{

    Q_GADGET
    Q_PROPERTY(QString first_name READ getFirst_name WRITE setFirst_name)
    Q_PROPERTY(QString last_name READ getLast_name WRITE setLast_name)
    Q_PROPERTY(QString identification_number READ getIdentification_number WRITE setIdentification_number)
    Q_PROPERTY(QString driver_permit_number READ getDriver_permit_number WRITE setDriver_permit_number)
    Q_PROPERTY(QString passport_number READ getPassport_number WRITE setPassport_number)
    Q_PROPERTY(DateTime date_of_birth READ getDate_of_birth WRITE setDate_of_birth)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
    virtual void registerConverter() override;

    QString getFirst_name() const;
    void setFirst_name(const QString value);

    QString getLast_name() const;
    void setLast_name(const QString value);

    QString getIdentification_number() const;
    void setIdentification_number(const QString value);

    QString getDriver_permit_number() const;
    void setDriver_permit_number(const QString value);

    QString getPassport_number() const;
    void setPassport_number(const QString value);

    DateTime getDate_of_birth() const;
    void setDate_of_birth(const DateTime value);

private:
    QString first_name;
    QString last_name;
    QString identification_number;
    QString driver_permit_number;
    QString passport_number;
    DateTime date_of_birth;
};

Q_DECLARE_METATYPE(Person)

#endif // PERSON_H