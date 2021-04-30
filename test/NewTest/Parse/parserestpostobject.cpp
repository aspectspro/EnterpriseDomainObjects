#include "parserestpostobject.h"

ParseRestPostObject::ParseRestPostObject(ParseConfiguration configuration) : ParseRestObjectsApi(configuration){

}

QJsonObject ParseRestPostObject::createObject(QString className, ParseBaseClass &domainObject){
    paths->append(className);

    QJsonDocument doc;
    doc.setObject(domainObject.stripParseObject());
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

    ParseBaseRestResponse responseObject;
    responseObject.fromJson(response);

    if(responseObject.getError().length() > 0)
        throw std::exception(responseObject.getError().toUtf8());

    ParseDate createdAt;
    createdAt.setIso(responseObject.getCreatedAt());

    domainObject.setObjectId(responseObject.getObjectId());
    domainObject.setCreatedAt(createdAt);
    domainObject.setUpdatedAt(createdAt);

    return response;
}
