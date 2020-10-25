#ifndef ORGANIZATION_H
#define ORGANIZATION_H
#include "abstractparty.h"

class Organization : public AbstractParty, public DomainCloneTemplate<Organization>{

    Q_GADGET
    Q_PROPERTY(QString company_name READ getCompany_name WRITE setCompany_name)

public:
    QString getCompany_name() const;
    void setCompany_name(const QString &value);

private:
    QString company_name;

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override
    {
        return staticMetaObject;
    }
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

#endif // ORGANIZATION_H
