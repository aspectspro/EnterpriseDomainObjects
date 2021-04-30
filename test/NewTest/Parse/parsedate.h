#ifndef PARSEDATE_H
#define PARSEDATE_H
#include "../src/EnterpriseDomainObjects.h"

struct ParseDate : public AbstractDomainObject{

    Q_GADGET
    Q_PROPERTY(QString __type READ getType WRITE setType)
    Q_PROPERTY(QString iso READ getIso WRITE setIso)


public:
    ParseDate(){
        registerConverter();
    }

    QString getIso() const;
    void setIso(const QString &value);

    QString getType() const;
    void setType(const QString &value);

private:
    QString type = "Date";
    QString iso;

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
    virtual void registerConverter() override;
};

Q_DECLARE_METATYPE(ParseDate)
#endif // PARSEDATE_H
