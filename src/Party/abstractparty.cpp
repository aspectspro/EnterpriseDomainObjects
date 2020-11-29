#include "abstractparty.h"

QString AbstractParty::getTelephone_number() const
{
    return telephone_number;
}

void AbstractParty::setTelephone_number(const QString value)
{
    telephone_number = value;
}

QString AbstractParty::getAddress() const
{
    return address;
}

void AbstractParty::setAddress(const QString value)
{
    address = value;
}

QString AbstractParty::getEmail_address() const
{
    return email_address;
}

void AbstractParty::setEmail_address(const QString value)
{
    email_address = value;
}

QString AbstractParty::getId() const
{
    return id;
}

void AbstractParty::setId(const QString value)
{
    id = value;
}



