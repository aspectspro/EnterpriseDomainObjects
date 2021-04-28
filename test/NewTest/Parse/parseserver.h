#ifndef PARSESERVER_H
#define PARSESERVER_H
#include "parseconfiguration.h"
#include "pathbuilderinterface.h"
#include <QtNetwork>

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
    std::unique_ptr<PathBuilderInterface> paths;
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

struct ParseCreateObjectResponse : public AbstractDomainObject{

    Q_GADGET
    Q_PROPERTY(QString objectId READ getObjectId WRITE setObjectId)
    Q_PROPERTY(QString createdAt READ getCreatedAt WRITE setCreatedAt)
    Q_PROPERTY(QString error READ getError WRITE setError)

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

    QString getError() const;
    void setError(const QString &value);

private:
    QString objectId, createdAt, error;
};

Q_DECLARE_METATYPE(ParseCreateObjectResponse)


struct ParsePostObject : public ParseObjectsApi{

public:
    ParsePostObject(const ParseConfiguration &configuration) : ParseObjectsApi(configuration){

    }

    QJsonObject createObject(QString className, ParseBaseObject& domainObject){
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

        ParseCreateObjectResponse responseObject;
        responseObject.fromJson(response);

        if(responseObject.getError().length() > 0)
            throw std::exception(responseObject.getError().toUtf8());

        domainObject.setObjectId(responseObject.getObjectId());
        domainObject.setCreatedAt(responseObject.getCreatedAt());
        domainObject.setUpdatedAt(responseObject.getCreatedAt());

        return response;
    }

};

struct ParseGetObject : public ParseObjectsApi{

public:
    ParseGetObject(const ParseConfiguration &configuration) : ParseObjectsApi(configuration){}

    template<typename T>
    std::unique_ptr<T> getObject(QString className, QString objectId){

        if(objectId.length() == 0)
            throw std::exception("Empty objectId");

        paths->append(className).append(objectId);

        QJsonDocument doc;
        auto request = getRequest();
        auto reply = network.get(request);

        QEventLoop loop;
        QJsonObject response;

        QObject::connect(reply,&QNetworkReply::finished,[&response,&loop,&reply](){
            auto json = QJsonDocument::fromJson(reply->readAll());
            response = json.object();
            loop.quit();
        });
        loop.exec();

        ParseCreateObjectResponse res;
        res.fromJson(response);
        if(res.getError().length() > 0)
            throw std::exception(res.getError().toUtf8());

        auto _type = std::make_unique<T>();
        auto _cast = dynamic_cast<ParseBaseObject*>(_type.get());

        if(_cast != nullptr)
            _cast->fromJson(response);

        return std::move(_type);
    }
};

struct ParseDeleteObject : public ParseObjectsApi{

public:
    ParseDeleteObject(const ParseConfiguration &configuration) : ParseObjectsApi(configuration){}

    QJsonObject deleteByObjectId(QString className, QString objectId){

        if(objectId.length() == 0)
            throw std::exception("Empty objectId");

        paths->append(className).append(objectId);

        QJsonDocument doc;
        auto request = getRequest();
        auto reply = network.deleteResource(request);

        QEventLoop loop;
        QJsonObject response;

        QObject::connect(reply,&QNetworkReply::finished,[&response,&loop,&reply](){
            auto json = QJsonDocument::fromJson(reply->readAll());
            response = json.object();
            loop.quit();
        });
        loop.exec();

        ParseCreateObjectResponse res;
        res.fromJson(response);
        if(res.getError().length() > 0)
            throw std::exception(res.getError().toUtf8());

        return response;

    }

};



#endif // PARSESERVER_H
