#include "pathbuilderinterface.h"


UrlPathBuilder::UrlPathBuilder(QString resetTo){
    this->resetTo = resetTo;

    reset();
}

PathBuilderInterface &UrlPathBuilder::reset()
{
    pathToReturn = resetTo;
    return *this;
}

QString UrlPathBuilder::build()
{
    auto _return = pathToReturn;

    if(_return.length() != 0){

        if(_return.at(0) != separator())
            _return = _return.prepend(separator());

        if(_return.at(_return.length() - 1) != separator())
            _return = _return.append(separator());

    }

    reset();
    return _return;
}

PathBuilderInterface &UrlPathBuilder::append(QString path)
{
    if(path.length() == 0)
        return *this;

    if(pathToReturn.length() == 0)
        pathToReturn = pathToReturn.append(separator());
    else if(pathToReturn.at(pathToReturn.length() - 1) != separator())
        pathToReturn = pathToReturn.append(separator());

    pathToReturn = pathToReturn.append(path);
    return *this;
}

QString UrlPathBuilder::separator()
{
    return QString("/");
}
