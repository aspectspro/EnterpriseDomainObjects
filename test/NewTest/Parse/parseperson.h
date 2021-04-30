#ifndef PARSEPERSON_H
#define PARSEPERSON_H
#include "parsebaseclass.h"


struct ParsePerson : public ParseBaseClass{

    Q_GADGET

    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName)
    Q_PROPERTY(QString middleName READ getMiddleName WRITE setMiddleName)
public:

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getMiddleName() const;
    void setMiddleName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

private:
    QString firstName, middleName, lastName;


    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
};

Q_DECLARE_METATYPE(ParsePerson)

#endif // PARSEPERSON_H
