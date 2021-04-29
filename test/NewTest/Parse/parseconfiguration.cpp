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

QString ParsePerson::getFirstName() const
{
    return firstName;
}

void ParsePerson::setFirstName(const QString &value)
{
    firstName = value;
}

QString ParsePerson::getMiddleName() const
{
    return middleName;
}

void ParsePerson::setMiddleName(const QString &value)
{
    middleName = value;
}

QString ParsePerson::getLastName() const
{
    return lastName;
}

void ParsePerson::setLastName(const QString &value)
{
    lastName = value;
}


const QMetaObject &ParsePerson::metaObject() const
{
    return this->staticMetaObject;
}

QString ParseDate::getIso() const
{
    return iso;
}

void ParseDate::setIso(const QString &value)
{
    iso = value;
}

QString ParseDate::getType() const
{
    return type;
}

void ParseDate::setType(const QString &value)
{
    type = value;
}

const QMetaObject &ParseDate::metaObject() const
{
    return this->staticMetaObject;
}

void ParseDate::registerConverter()
{
    if(QMetaType::hasRegisteredConverterFunction<ParseDate,QJsonValue>())
        return;

    qRegisterMetaType<ParseDate>();

    QMetaType::registerConverter<ParseDate,QJsonValue>([=](ParseDate dateTime) -> QJsonValue{
        return dateTime.toJsonObject();

    });


    QMetaType::registerConverter<QJsonValue,ParseDate>([=](QJsonValue dateTime) -> ParseDate{
        ParseDate _date;
        _date.fromJson(dateTime.toObject());
        return _date;
    });

    QMetaType::registerConverter<QString,ParseDate>([=](QString dateTime) -> ParseDate{
        ParseDate _date;
        _date.setIso(dateTime);
        return _date;
    });
}

