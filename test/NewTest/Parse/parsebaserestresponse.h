#ifndef PARSEBASEHTTPRESPONSE_H
#define PARSEBASEHTTPRESPONSE_H
#include "parserestrequest.h"


struct ParseBaseRestResponse : public AbstractDomainObject{

    Q_GADGET
    Q_PROPERTY(QString objectId READ getObjectId WRITE setObjectId)
    Q_PROPERTY(QString createdAt READ getCreatedAt WRITE setCreatedAt)
    Q_PROPERTY(QString updatedAt READ getUpdatedAt WRITE setUpdatedAt)
    Q_PROPERTY(QString error READ getError WRITE setError)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    QString getObjectId() const;
    void setObjectId(const QString &value);

    QString getCreatedAt() const;
    void setCreatedAt(const QString &value);

    QString getError() const;
    void setError(const QString &value);

    QString getUpdatedAt() const;
    void setUpdatedAt(const QString &value);

private:
    QString objectId, createdAt, error, updatedAt;
};

Q_DECLARE_METATYPE(ParseBaseRestResponse)


#endif // PARSEBASEHTTPRESPONSE_H
