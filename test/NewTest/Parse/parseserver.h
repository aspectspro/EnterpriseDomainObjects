#ifndef PARSESERVER_H
#define PARSESERVER_H
#include "parseconfiguration.h"
#include <QtNetwork>

struct PathBuilder{
public:
    virtual PathBuilder& reset() = 0;
    virtual QString build() = 0;
    virtual PathBuilder& append(QString path) = 0;
    virtual QString separator() = 0;

protected:
    QString pathToReturn;
    QString resetTo;
};

struct UrlPathBuilder : public PathBuilder{

    // PathBuilder interface
public:

    UrlPathBuilder(QString resetTo = ""){
        this->resetTo = resetTo;

        reset();
    }

    virtual PathBuilder &reset() override
    {
        pathToReturn = resetTo;
        return *this;
    }

    virtual QString build() override
    {
        auto _return = pathToReturn;

        if(_return.length() != 0){

            if(_return.at(0) != separator())
                _return = _return.prepend(separator());

            if(_return.at(_return.length() - 1) != separator())
                _return = _return.append(separator());

        }

        reset();
        return _return;
    }

    virtual PathBuilder &append(QString path) override
    {
        if(path.length() == 0)
            return *this;

        if(pathToReturn.length() == 0)
            pathToReturn = pathToReturn.append(separator());
        else if(pathToReturn.at(pathToReturn.length() - 1) != separator())
            pathToReturn = pathToReturn.append(separator());

        pathToReturn = pathToReturn.append(path);
        return *this;
    }

protected:
    virtual QString separator() override
    {
        return QString("/");
    }
};

struct ParseRequestsApi{

public:
    ParseRequestsApi(const ParseConfiguration &configuration) : configuration(configuration){
        paths = std::make_unique<UrlPathBuilder>();
    }

    virtual QNetworkRequest getRequest(){

        QNetworkRequest request;

        QUrl url;
        url.setHost(configuration.getServerDomain());
        url.setPort(configuration.getPort());
        url.setPath(paths->build());
        url.setScheme("http");

        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
        request.setRawHeader("X-Parse-Application-Id", configuration.getApplicationId().toUtf8());
        request.setRawHeader("X-Parse-REST-API-Key", configuration.getRestApiKey().toUtf8());

        return request;
    };

protected:
    std::unique_ptr<PathBuilder> paths;
    const ParseConfiguration &configuration;
    QNetworkAccessManager network;

};

struct ParseObjectsApi : public ParseRequestsApi{
public:
    ParseObjectsApi(const ParseConfiguration& configuration) : ParseRequestsApi(configuration){
        paths = std::make_unique<UrlPathBuilder>(
                    configuration.getMountPath().append(paths->separator()).append("classes"));
    }
};

struct ParseCreateObject : public ParseObjectsApi{

public:
    ParseCreateObject(const ParseConfiguration &configuration) : ParseObjectsApi(configuration){

    }

    QJsonObject createObject(QString className, AbstractDomainObject& domainObject){
        paths->append(className);

        QJsonDocument doc;
        doc.setObject(domainObject.toJsonObject());
        auto request = getRequest();
        auto reply = network.post(request,doc.toJson());

        QEventLoop loop;
        QJsonObject response;

        QObject::connect(reply,&QNetworkReply::finished,[&response,&loop,&reply](){
            auto json = QJsonDocument::fromJson(reply->readAll());
            response = json.object();
            loop.quit();
        });
        loop.exec();

        return response;
    }

};

struct ParseGetObject : public ParseObjectsApi{

public:
    ParseGetObject(const ParseConfiguration &configuration) : ParseObjectsApi(configuration){}

    QNetworkReply* getObject(QString className, QString objectId){
        paths->append(className).append(objectId);
        auto request = getRequest();
        auto reply = network.get(request);

        return reply;
    }

};

struct ParseCreateResponse : public AbstractDomainObject{

    Q_GADGET
    Q_PROPERTY(QString objectId READ getObjectId WRITE setObjectId)
    Q_PROPERTY(QString createdAt READ getCreatedAt WRITE setCreatedAt)

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override
    {
        return this->staticMetaObject;
    }

    QString getObjectId() const;
    void setObjectId(const QString &value);

    QString getCreatedAt() const;
    void setCreatedAt(const QString &value);

private:
    QString objectId, createdAt;
};

Q_DECLARE_METATYPE(ParseCreateResponse)

#endif // PARSESERVER_H
