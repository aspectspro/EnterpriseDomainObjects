#include "parsedate.h"


void ParseDate::registerConverter()
{
    if(QMetaType::hasRegisteredConverterFunction<ParseDate,QJsonValue>())
        return;

    qRegisterMetaType<ParseDate>();

    QMetaType::registerConverter<ParseDate,QJsonValue>([=](ParseDate dateTime) -> QJsonValue{
        return dateTime.toJsonObject();

    });


    QMetaType::registerConverter<QJsonValue,ParseDate>([=](QJsonValue dateTime) -> ParseDate{
        ParseDate _date;
        _date.fromJson(dateTime.toObject());
        return _date;
    });

    QMetaType::registerConverter<QString,ParseDate>([=](QString dateTime) -> ParseDate{
        ParseDate _date;
        _date.setIso(dateTime);
        return _date;
    });
}
