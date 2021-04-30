#include "parsebaseclass.h"

const QMetaObject &ParseBaseClass::metaObject() const
{
    return this->staticMetaObject;
}

QString ParseBaseClass::getObjectId() const
{
    return objectId;
}

void ParseBaseClass::setObjectId(const QString &value)
{
    objectId = value;
}

ParseDate ParseBaseClass::getCreatedAt() const
{
    return createdAt;
}

void ParseBaseClass::setCreatedAt(const ParseDate &value)
{
    createdAt = value;
}

ParseDate ParseBaseClass::getUpdatedAt() const
{
    return updatedAt;
}

void ParseBaseClass::setUpdatedAt(const ParseDate &value)
{
    updatedAt = value;
}

QJsonObject ParseBaseClass::stripParseObject(){
    auto base = this->toJsonObject();

    ParseBaseClass _toRemove;

    auto keys = _toRemove.toJsonObject().keys();

    foreach (auto key, keys) {
        base.remove(key);
    }

    injectStrip(base);

    return base;
}
