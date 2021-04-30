#ifndef PARSEBASECLASS_H
#define PARSEBASECLASS_H
#include "parsedate.h"

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
    QJsonObject stripParseObject();

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

#endif // PARSEBASECLASS_H
