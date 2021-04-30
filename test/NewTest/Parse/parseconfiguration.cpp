#include "parseconfiguration.h"

std::unique_ptr<ParseConfiguration> ParseConfiguration::_instance = 0;

ParseConfiguration::ParseConfiguration()
{

}

ParseConfiguration *ParseConfiguration::getInstance(){
    if(_instance.get() == nullptr)
        _instance = std::make_unique<ParseConfiguration>();
    return _instance.get();
}

const QMetaObject &ParseConfiguration::metaObject() const
{
    return this->staticMetaObject;
}

QString ParseConfiguration::getServerDomain() const
{
    return serverDomain;
}

ParseConfiguration &ParseConfiguration::setServerDomain(const QString &value)
{
    serverDomain = value;
    return *this;
}

QString ParseConfiguration::getApplicationId() const
{
    return applicationId;

}

ParseConfiguration &ParseConfiguration::setApplicationId(const QString &value)
{
    applicationId = value;
    return *this;
}

QString ParseConfiguration::getMasterKey() const
{
    return masterKey;
}

ParseConfiguration &ParseConfiguration::setMasterKey(const QString &value)
{
    masterKey = value;
    return *this;
}

QString ParseConfiguration::getClientKey() const
{
    return clientKey;
}

ParseConfiguration &ParseConfiguration::setClientKey(const QString &value)
{
    clientKey = value;
    return *this;
}

QString ParseConfiguration::getRestApiKey() const
{
    return restApiKey;
}

ParseConfiguration &ParseConfiguration::setRestApiKey(const QString &value)
{
    restApiKey = value;
    return *this;
}

int ParseConfiguration::getPort() const
{
    return port;
}

ParseConfiguration &ParseConfiguration::setPort(int value)
{
    port = value;
    return *this;
}

QString ParseConfiguration::getMountPath() const
{
    return mountPath;
}

ParseConfiguration &ParseConfiguration::setMountPath(const QString &value)
{
    mountPath = value;
    return *this;
}



