#ifndef PARSERESTDELETEOBJECT_H
#define PARSERESTDELETEOBJECT_H
#include "parserestobjectsapi.h"

struct ParseRestDeleteObject : public ParseRestObjectsApi{

public:
    ParseRestDeleteObject(ParseConfiguration configuration);

    QJsonObject deleteByObjectId(QString className, QString objectId);
};

#endif // PARSERESTDELETEOBJECT_H
