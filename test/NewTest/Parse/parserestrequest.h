#ifndef PARSEHTTPREQUEST_H
#define PARSEHTTPREQUEST_H
#include "parseconfiguration.h"
#include "pathbuilderinterface.h"
#include <QtNetwork>

struct ParseRestRequest{

public:
    ParseRestRequest(ParseConfiguration configuration);

    virtual QNetworkRequest getRequest();

protected:
    std::unique_ptr<PathBuilderInterface> paths;
    ParseConfiguration configuration;
    QNetworkAccessManager network;

};

#endif // PARSEHTTPREQUEST_H
