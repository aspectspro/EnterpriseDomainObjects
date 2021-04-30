#ifndef PARSERESTPOSTOBJECT_H
#define PARSERESTPOSTOBJECT_H
#include "parserestobjectsapi.h"

struct ParseRestPostObject : public ParseRestObjectsApi{

public:
    ParseRestPostObject(ParseConfiguration configuration);

    QJsonObject createObject(QString className, ParseBaseClass& domainObject);

};

#endif // PARSERESTPOSTOBJECT_H
