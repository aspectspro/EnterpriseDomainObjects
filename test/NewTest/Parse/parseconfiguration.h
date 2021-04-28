#ifndef PARSECONFIGURATION_H
#define PARSECONFIGURATION_H

#include "../src/EnterpriseDomainObjects.h"

class ParseConfiguration : public AbstractDomainObject
{
    Q_GADGET
    Q_PROPERTY(QString serverDomain READ getServerDomain WRITE setServerDomain)
    Q_PROPERTY(QString applicationId READ getApplicationId WRITE setApplicationId)
    Q_PROPERTY(QString mountPath READ getMountPath WRITE setMountPath)
    Q_PROPERTY(QString masterKey READ getMasterKey WRITE setMasterKey)
    Q_PROPERTY(QString clientKey READ getClientKey WRITE setClientKey)
    Q_PROPERTY(QString restApiKey READ getRestApiKey WRITE setRestApiKey)
    Q_PROPERTY(int port READ getPort WRITE setPort)


    static std::unique_ptr<ParseConfiguration> _instance;

public:
    ParseConfiguration();

    static ParseConfiguration& getInstance();

    virtual const QMetaObject &metaObject() const override;

    QString getServerDomain() const;
    ParseConfiguration& setServerDomain(const QString &value);

    QString getApplicationId() const;
    ParseConfiguration& setApplicationId(const QString &value);

    QString getMasterKey() const;
    ParseConfiguration& setMasterKey(const QString &value);

    QString getClientKey() const;
    ParseConfiguration& setClientKey(const QString &value);

    QString getRestApiKey() const;
    ParseConfiguration& setRestApiKey(const QString &value);

    int getPort() const;
    ParseConfiguration& setPort(int value);

    QString getMountPath() const;
    ParseConfiguration& setMountPath(const QString &value);

private:
    QString serverDomain, applicationId, masterKey, clientKey, restApiKey, mountPath;
    int port = 0;
};

Q_DECLARE_METATYPE(ParseConfiguration)

struct ParseBaseObject : public AbstractDomainObject{

    Q_GADGET

    Q_PROPERTY(QString objectId READ getObjectId WRITE setObjectId)
    Q_PROPERTY(QJsonValue createdAt READ getCreatedAt WRITE setCreatedAt)
    Q_PROPERTY(QJsonValue updatedAt READ getUpdatedAt WRITE setUpdatedAt)

private:
    using AbstractDomainObject::generateId;
    QString objectId;
    QJsonValue createdAt, updatedAt;


    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    QString getObjectId() const;
    void setObjectId(const QString &value);

    QJsonValue getCreatedAt() const;
    void setCreatedAt(const QJsonValue &value);

    QJsonValue getUpdatedAt() const;
    void setUpdatedAt(const QJsonValue &value);
};

Q_DECLARE_METATYPE(ParseBaseObject)


struct ParsePerson : public ParseBaseObject{

    Q_GADGET

    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName)
    Q_PROPERTY(QString middleName READ getMiddleName WRITE setMiddleName)
public:

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getMiddleName() const;
    void setMiddleName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

private:
    QString firstName, middleName, lastName;


    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
};

Q_DECLARE_METATYPE(ParsePerson)

#endif // PARSECONFIGURATION_H
