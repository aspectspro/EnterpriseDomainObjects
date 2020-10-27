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

    /** copyFrom - //To move to AbstractDomainObjects. Used for copying from other classes. Use this
     * when loading sql and base class needs to be loaded.
     *
     */
    template<typename T>
    void copyFrom(AbstractDomainObject &domainObject){
        try {
            auto _party = dynamic_cast<T*>(&domainObject);
            this->fromJson(_party->toJsonObject());
        } catch (std::exception &e) {
            qInfo() << e.what();
        }
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



#endif // ABSTRACTPARTY_H
