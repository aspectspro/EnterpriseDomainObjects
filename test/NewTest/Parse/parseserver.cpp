#include "parseserver.h"

QString ParseCreateResponse::getObjectId() const
{
    return objectId;
}

void ParseCreateResponse::setObjectId(const QString &value)
{
    objectId = value;
}

QString ParseCreateResponse::getCreatedAt() const
{
    return createdAt;
}

void ParseCreateResponse::setCreatedAt(const QString &value)
{
    createdAt = value;
}
