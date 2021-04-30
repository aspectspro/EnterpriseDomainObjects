#ifndef PARSERESTGETOBJECT_H
#define PARSERESTGETOBJECT_H
#include "parserestobjectsapi.h"

struct ParseRestGetObject : public ParseRestObjectsApi{

public:
    ParseRestGetObject(ParseConfiguration configuration) : ParseRestObjectsApi(configuration){}

    template<typename T>
    std::unique_ptr<T> getObject(QString className, QString objectId){

        auto response = getObjectJson(className,objectId);

        auto _type = std::make_unique<T>();
        auto _cast = dynamic_cast<ParseBaseClass*>(_type.get());

        if(_cast != nullptr)
            _cast->fromJson(response);

        return std::move(_type);
    }

private:
    QJsonObject getObjectJson(QString &className, QString &objectId);
};

#endif // PARSERESTGETOBJECT_H
