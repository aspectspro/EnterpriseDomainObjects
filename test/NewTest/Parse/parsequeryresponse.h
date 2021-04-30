#ifndef PARSEQUERYRESPONSE_H
#define PARSEQUERYRESPONSE_H
#include "parsequery.h"

struct ParseQueryResponse : public ParseBaseRestResponse{

    Q_GADGET
    Q_PROPERTY(QJsonValue results READ getResults WRITE setResults)
public:
    QJsonValue getResults() const;
    void setResults(const QJsonValue &value);


private:
    QJsonValue results;


    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
};



Q_DECLARE_METATYPE(ParseQueryResponse)


#endif // PARSEQUERYRESPONSE_H
