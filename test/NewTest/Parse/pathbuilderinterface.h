#ifndef PATHBUILDERINTERFACE_H
#define PATHBUILDERINTERFACE_H
#include "../src/EnterpriseDomainObjects.h"

struct PathBuilderInterface{
public:
    virtual PathBuilderInterface& reset() = 0;
    virtual QString build() = 0;
    virtual PathBuilderInterface& append(QString path) = 0;
    virtual QString separator() = 0;

protected:
    QString pathToReturn;
    QString resetTo;
};

struct UrlPathBuilder : public PathBuilderInterface{

    // PathBuilder interface
public:

    UrlPathBuilder(QString resetTo = "");

    virtual PathBuilderInterface &reset() override;

    virtual QString build() override;

    virtual PathBuilderInterface &append(QString path) override;

protected:
    virtual QString separator() override;
};
#endif // PATHBUILDERINTERFACE_H
