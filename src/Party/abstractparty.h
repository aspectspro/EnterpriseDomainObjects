#ifndef ABSTRACTPARTY_H
#define ABSTRACTPARTY_H
#include "AbstractObjects.h"
#include "database.h"
#include <iostream>

class AbstractParty: public AbstractDomainObject{

    Q_GADGET

    Q_PROPERTY(QString telephone_number READ getTelephone_number WRITE setTelephone_number)
    Q_PROPERTY(QString address READ getAddress WRITE setAddress)
    Q_PROPERTY(QString email_address READ getEmail_address WRITE setEmail_address)
    Q_PROPERTY(QString id READ getId WRITE setId)

    // AbstractDomainObject interface
public:
    QString getTelephone_number() const;
    void setTelephone_number(const QString value);

    QString getAddress() const;
    void setAddress(const QString value);

    QString getEmail_address() const;
    void setEmail_address(const QString value);

    QString getId() const;
    void setId(const QString value);

    void copyBaseParty(AbstractParty &party){
        this->fromJson(party.toJsonObject());
    }

private:
    QString telephone_number;
    QString address;
    QString email_address;
    QString id;

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override
    {
        return staticMetaObject;
    }
};

class AbstractPartyMapper : public TemplateMapper<AbstractParty>{
    // AbstractMapper interface
public:
    virtual QString tableName() const override
    {
        return "party_abstractparty";
    }
};

class PartyModule : public SetupModule{

protected:
    SetupModule &createModule() override;
    SetupModule &installSchema() override;
    SetupModule &installData() override;
    SetupModule &upgradeSchema() override;
    SetupModule &upgradeData() override;
};

#endif // ABSTRACTPARTY_H
