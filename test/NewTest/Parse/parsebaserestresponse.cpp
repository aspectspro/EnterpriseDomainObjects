#include "parsebaserestresponse.h"


const QMetaObject &ParseBaseRestResponse::metaObject() const
{
    return this->staticMetaObject;
}

QString ParseBaseRestResponse::getObjectId() const
{
    return objectId;
}

void ParseBaseRestResponse::setObjectId(const QString &value)
{
    objectId = value;
}

QString ParseBaseRestResponse::getCreatedAt() const
{
    return createdAt;
}

void ParseBaseRestResponse::setCreatedAt(const QString &value)
{
    createdAt = value;
}

QString ParseBaseRestResponse::getError() const
{
    return error;
}

void ParseBaseRestResponse::setError(const QString &value)
{
    error = value;
}

QString ParseBaseRestResponse::getUpdatedAt() const
{
    return updatedAt;
}

void ParseBaseRestResponse::setUpdatedAt(const QString &value)
{
    updatedAt = value;
}
