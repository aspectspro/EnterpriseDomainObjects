#include "parseserver.h"

QString ParseCreateObjectResponse::getObjectId() const
{
    return objectId;
}

void ParseCreateObjectResponse::setObjectId(const QString &value)
{
    objectId = value;
}

QString ParseCreateObjectResponse::getCreatedAt() const
{
    return createdAt;
}

void ParseCreateObjectResponse::setCreatedAt(const QString &value)
{
    createdAt = value;
}

QString ParseCreateObjectResponse::getError() const
{
    return error;
}

void ParseCreateObjectResponse::setError(const QString &value)
{
    error = value;
}
