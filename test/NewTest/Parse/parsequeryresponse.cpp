#include "parsequeryresponse.h"

QJsonValue ParseQueryResponse::getResults() const
{
    return results;
}

void ParseQueryResponse::setResults(const QJsonValue &value)
{
    results = value;
}

const QMetaObject &ParseQueryResponse::metaObject() const
{
    return this->staticMetaObject;
}

