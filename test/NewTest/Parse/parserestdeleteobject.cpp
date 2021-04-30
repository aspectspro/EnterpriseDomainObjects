#include "parserestdeleteobject.h"

ParseRestDeleteObject::ParseRestDeleteObject(ParseConfiguration configuration) : ParseRestObjectsApi(configuration){}

QJsonObject ParseRestDeleteObject::deleteByObjectId(QString className, QString objectId){

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

    ParseBaseRestResponse res;
    res.fromJson(response);
    if(res.getError().length() > 0)
        throw std::exception(res.getError().toUtf8());

    return response;
}
