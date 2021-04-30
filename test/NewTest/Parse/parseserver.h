#ifndef PARSESERVER_H
#define PARSESERVER_H
#include "parserestdeleteobject.h"
#include "parserestgetobject.h"
#include "parserestputobject.h"
#include "parserestpostobject.h"
#include "parsequeryresponse.h"

struct ParseRestQueryObject : public ParseRestObjectsApi{

public:
    ParseRestQueryObject(ParseConfiguration configuration) : ParseRestObjectsApi(configuration){}

    template<typename T>
    QList<std::shared_ptr<T>> query(ParseQuery query){

        auto results = internalQuery(query);

        QList<std::shared_ptr<T>> list;

        foreach (auto value, results) {
            auto _type = std::make_shared<T>();
            auto _cast = dynamic_cast<ParseBaseClass*>(_type.get());

            if(_cast != nullptr)
                _cast->fromJson(value.toObject());
            list.append(_type);
        }

        return list;
    }


private:
    QJsonArray internalQuery(ParseQuery &query){

        if(query.getClassName().isNull())
            throw std::exception("Empty class name");

        paths->append(query.getClassName());

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

        ParseQueryResponse res;
        res.fromJson(response);
        if(res.getError().length() > 0)
            throw std::exception(res.getError().toUtf8());

        return res.getResults().toArray();

//        auto _type = std::make_unique<T>();
//        auto _cast = dynamic_cast<ParseBaseClass*>(_type.get());

//        if(_cast != nullptr)
//            _cast->fromJson(response);

    }

private:

};

struct ParseMapper{

public:
    virtual QString className() = 0;

    ParseMapper() :_post(*ParseConfiguration::getInstance())
      ,_get(*ParseConfiguration::getInstance())
      ,_delete(*ParseConfiguration::getInstance())
      ,_put(*ParseConfiguration::getInstance()){

    }

    ParseMapper& postObject(ParseBaseClass& parseObject){
        _post.createObject(className(),parseObject);
        return *this;
    }

    template<typename T>
    std::unique_ptr<T> getObject(QString objectId){
        return std::move(_get.getObject<T>(className(),objectId));
    }

    ParseMapper& deleteObject(QString objectId){
        _delete.deleteByObjectId(className(),objectId);
        return *this;
    }

    ParseMapper& putObject(ParseBaseClass& parseObject){
        _put.updateObject(className(),parseObject);
        return *this;
    }

protected:
    ParseRestPostObject _post;
    ParseRestGetObject _get;
    ParseRestDeleteObject _delete;
    ParseRestPutObject _put;
};



#endif // PARSESERVER_H
