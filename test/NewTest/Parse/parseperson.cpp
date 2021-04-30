#include "parseperson.h"


QString ParsePerson::getFirstName() const
{
    return firstName;
}

void ParsePerson::setFirstName(const QString &value)
{
    firstName = value;
}

QString ParsePerson::getMiddleName() const
{
    return middleName;
}

void ParsePerson::setMiddleName(const QString &value)
{
    middleName = value;
}

QString ParsePerson::getLastName() const
{
    return lastName;
}

void ParsePerson::setLastName(const QString &value)
{
    lastName = value;
}


const QMetaObject &ParsePerson::metaObject() const
{
    return this->staticMetaObject;
}

QString ParseDate::getIso() const
{
    return iso;
}

void ParseDate::setIso(const QString &value)
{
    iso = value;
}

QString ParseDate::getType() const
{
    return type;
}

void ParseDate::setType(const QString &value)
{
    type = value;
}

const QMetaObject &ParseDate::metaObject() const
{
    return this->staticMetaObject;
}
