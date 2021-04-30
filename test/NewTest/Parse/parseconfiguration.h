#ifndef PARSECONFIGURATION_H
#define PARSECONFIGURATION_H
#include "../src/EnterpriseDomainObjects.h"
#include "parsebaseclass.h"

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

    static ParseConfiguration* getInstance();

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





#endif // PARSECONFIGURATION_H
