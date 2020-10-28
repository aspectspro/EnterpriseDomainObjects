#ifndef PERSON_H
#define PERSON_H
#include "abstractparty.h"

class DateTime{

    Q_GADGET
    Q_PROPERTY(int timestamp READ getTimestamp WRITE setTimestamp)
public:
    DateTime();
    Q_INVOKABLE int getTimestamp() const;
    Q_INVOKABLE void setTimestamp(int value);
    Q_INVOKABLE QString getDateTimeAsString();
    Q_INVOKABLE QString toString();
    Q_INVOKABLE QString toDate();
    Q_INVOKABLE QString toTime();
    Q_INVOKABLE static DateTime getNow();

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
    Person();
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

class PersonMapper : public TemplateMapper<Person>{


    // AbstractMapper interface
public:
    virtual QString tableName() const override;

protected:
    virtual void injectInsert(AbstractDomainObject &domainObject) const override;
    virtual void injectUpdate(AbstractDomainObject &domainObject) const override;
    virtual void injectRemove(AbstractDomainObject &domainObject) const override;
    virtual void injectLoad(AbstractDomainObject &domainObject) const override;
};

class Employee : public Person, public DomainCloneTemplate<Employee>{

    Q_GADGET
    Q_PROPERTY(QString bir_number READ getBir_number WRITE setBir_number)
    Q_PROPERTY(QString nis_number READ getNis_number WRITE setNis_number)
    Q_PROPERTY(DateTime date_of_employment READ getDate_of_employment WRITE setDate_of_employment)
    Q_PROPERTY(DateTime date_of_discharge READ getDate_of_discharge WRITE setDate_of_discharge)

    // AbstractDomainObject interface
public:
    Employee();
    using DomainCloneTemplate<Employee>::clone;

    virtual const QMetaObject &metaObject() const override;
    virtual void registerConverter() override;

    QString getBir_number() const;
    void setBir_number(const QString value);

    QString getNis_number() const;
    void setNis_number(const QString value);

    DateTime getDate_of_employment() const;
    void setDate_of_employment(const DateTime value);

    DateTime getDate_of_discharge() const;
    void setDate_of_discharge(const DateTime value);

private:
    QString bir_number;
    QString nis_number;
    DateTime date_of_employment;
    DateTime date_of_discharge;
};

Q_DECLARE_METATYPE(Employee)

class EmployeeMapper : public TemplateMapper<Employee>{


    // AbstractMapper interface
public:
    virtual QString tableName() const override;

protected:
    virtual void injectInsert(AbstractDomainObject &domainObject) const override;
    virtual void injectUpdate(AbstractDomainObject &domainObject) const override;
    virtual void injectRemove(AbstractDomainObject &domainObject) const override;
    virtual void injectLoad(AbstractDomainObject &domainObject) const override;
};

#endif // PERSON_H
