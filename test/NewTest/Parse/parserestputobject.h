#ifndef PARSERESTPUTOBJECT_H
#define PARSERESTPUTOBJECT_H
#include "parserestobjectsapi.h"

struct ParseRestPutObject : public ParseRestObjectsApi{

public:
    ParseRestPutObject(ParseConfiguration configuration) : ParseRestObjectsApi(configuration){}

    QJsonObject updateObject(QString className, ParseBaseClass& domainObject);

};


#endif // PARSERESTPUTOBJECT_H
