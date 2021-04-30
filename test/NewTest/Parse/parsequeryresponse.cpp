#include "parsequeryresponse.h"

QJsonArray ParseQueryResponse::getResults() const
{
    return results;
}

void ParseQueryResponse::setResults(const QJsonArray &value)
{
    results = value;
}

const QMetaObject &ParseQueryResponse::metaObject() const
{
    return this->staticMetaObject;
}

