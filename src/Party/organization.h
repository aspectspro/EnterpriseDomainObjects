#ifndef ORGANIZATION_H
#define ORGANIZATION_H
#include "abstractparty.h"

class Organization : public AbstractParty, public DomainCloneTemplate<Organization>{

    Q_GADGET
    Q_PROPERTY(QString company_name READ getCompany_name WRITE setCompany_name)

public:
    Organization();
    QString getCompany_name() const;
    void setCompany_name(const QString &value);

private:
    QString company_name;

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    // AbstractDomainObject interface
public:
    virtual void registerConverter() override;
};

Q_DECLARE_METATYPE(Organization)

class OrganizationMapper : public TemplateMapper<Organization>{


    // AbstractMapper interface
public:
    virtual QString tableName() const override
    {
        return "party_organization";
    }

protected:
    virtual void injectInsert(AbstractDomainObject &domainObject) const override;
    virtual void injectUpdate(AbstractDomainObject &domainObject) const override;
    virtual void injectRemove(AbstractDomainObject &domainObject) const override;
    virtual void injectLoad(AbstractDomainObject &domainObject) const override;
};

class Person : public AbstractParty, public DomainCloneTemplate<Person>{

    Q_GADGET
    Q_PROPERTY(QString first_name READ getFirst_name WRITE setFirst_name)
    Q_PROPERTY(QString last_name READ getLast_name WRITE setLast_name)
    Q_PROPERTY(QString identification_number READ getIdentification_number WRITE setIdentification_number)
    Q_PROPERTY(QString driver_permit_number READ getDriver_permit_number WRITE setDriver_permit_number)
    Q_PROPERTY(QString passport_number READ getPassport_number WRITE setPassport_number)
    Q_PROPERTY(QDateTime date_of_birth READ getDate_of_birth WRITE setDate_of_birth)

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

    QDateTime getDate_of_birth() const;
    void setDate_of_birth(const QDateTime value);

private:
    QString first_name;
    QString last_name;
    QString identification_number;
    QString driver_permit_number;
    QString passport_number;
    QDateTime date_of_birth;
};

Q_DECLARE_METATYPE(Person)

#endif // ORGANIZATION_H
