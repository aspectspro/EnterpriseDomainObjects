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

struct ParseDate : public AbstractDomainObject{

    Q_GADGET
    Q_PROPERTY(QString __type READ getType WRITE setType)
    Q_PROPERTY(QString iso READ getIso WRITE setIso)


public:
    ParseDate(){
        registerConverter();
    }

    QString getIso() const;
    void setIso(const QString &value);

    QString getType() const;
    void setType(const QString &value);

private:
    QString type = "Date";
    QString iso;

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;
    virtual void registerConverter() override;
};

Q_DECLARE_METATYPE(ParseDate)

/**
 * @brief The ParseBaseObject struct - This is the data interface for ParseClass
 */
struct ParseBaseClass : public AbstractDomainObject{

    Q_GADGET

    Q_PROPERTY(QString objectId READ getObjectId WRITE setObjectId)
    Q_PROPERTY(ParseDate createdAt READ getCreatedAt WRITE setCreatedAt)
    Q_PROPERTY(ParseDate updatedAt READ getUpdatedAt WRITE setUpdatedAt)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override;

    QString getObjectId() const;
    void setObjectId(const QString &value);

    ParseDate getCreatedAt() const;
    void setCreatedAt(const ParseDate &value);

    ParseDate getUpdatedAt() const;
    void setUpdatedAt(const ParseDate &value);

    /**
     * @brief stripParseObject - Strips Parse object from generated Fields
     * @return
     */
    QJsonObject stripParseObject(){
        auto base = this->toJsonObject();

        ParseBaseClass _toRemove;

        auto keys = _toRemove.toJsonObject().keys();

        foreach (auto key, keys) {
            base.remove(key);
        }

        injectStrip(base);

        return base;
    }

protected:
    /**
     * @brief injectStrip - Use this to remove other keys
     * @example
     *
     * json.remove("KeyName");
     *
     * @param json
     * @return
     */
    virtual ParseBaseClass& injectStrip(QJsonObject &json){
        Q_UNUSED(json)
        return *this;
    }

private:
    using AbstractDomainObject::generateId;
    QString objectId;
    ParseDate createdAt, updatedAt;

};

Q_DECLARE_METATYPE(ParseBaseClass)


struct ParsePerson : public ParseBaseClass{

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
