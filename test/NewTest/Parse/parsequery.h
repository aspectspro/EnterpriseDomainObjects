#ifndef PARSEQUERY_H
#define PARSEQUERY_H
#include "parsebaserestresponse.h"

struct ParseQuery{

public:
    QString getClassName() const;
    void setClassName(const QString &value);

private:
    QString className;
};


#endif // PARSEQUERY_H
