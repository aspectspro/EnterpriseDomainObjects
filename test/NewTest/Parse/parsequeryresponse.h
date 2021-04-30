#ifndef PARSEQUERYRESPONSE_H
#define PARSEQUERYRESPONSE_H
#include "parsequery.h"

struct ParseQueryResponse : public ParseBaseRestResponse{

    Q_GADGET
    Q_PROPERTY(QJsonArray results READ getResults WRITE setResults)
public:
    QJsonArray getResults() const;
    void setResults(const QJsonArray &value);


private:
    QJsonArray results;


    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
};



Q_DECLARE_METATYPE(ParseQueryResponse)


#endif // PARSEQUERYRESPONSE_H
