#include "parserestrequest.h"



ParseRestRequest::ParseRestRequest(ParseConfiguration configuration) : configuration(configuration){
    paths = std::make_unique<UrlPathBuilder>();
}

QNetworkRequest ParseRestRequest::getRequest(){

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
}
