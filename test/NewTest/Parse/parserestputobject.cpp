#include "parserestputobject.h"


QJsonObject ParseRestPutObject::updateObject(QString className, ParseBaseClass &domainObject){
    paths->append(className).append(domainObject.getObjectId());

    QJsonDocument doc;
    doc.setObject(domainObject.stripParseObject());

    auto request = getRequest();
    auto reply = network.put(request,doc.toJson());

    QEventLoop loop;
    QJsonObject response;

    QObject::connect(reply,&QNetworkReply::finished,[&response,&loop,&reply](){
        auto json = QJsonDocument::fromJson(reply->readAll());
        response = json.object();
        loop.quit();
    });
    loop.exec();

    ParseBaseRestResponse responseObject;
    responseObject.fromJson(response);

    if(responseObject.getError().length() > 0)
        throw std::exception(responseObject.getError().toUtf8());

    ParseDate updatedAt;
    updatedAt.setIso(responseObject.getUpdatedAt());

    domainObject.setUpdatedAt(updatedAt);

    return response;
}
