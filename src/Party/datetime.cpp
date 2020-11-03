#include "datetime.h"
DateTime::DateTime()
{
    registerMetaType();
}

int DateTime::getTimestamp() const
{
    return timestamp;
}

void DateTime::setTimestamp(int value)
{
    timestamp = value;
}

QString DateTime::getDateTimeAsString()
{
    return QDateTime::fromSecsSinceEpoch(getTimestamp()).toString("dddd dd MMMM yyyy, hh:mm:ss ap");
}

QString DateTime::toString()
{
    return getDateTimeAsString();
}

QString DateTime::toDate()
{
    return QDateTime::fromSecsSinceEpoch(getTimestamp()).toString("dddd dd MMMM yyyy");
}

QString DateTime::toTime()
{
    return QDateTime::fromSecsSinceEpoch(getTimestamp()).toString("hh:mm:ss ap");
}

DateTime DateTime::getNow()
{
    DateTime time;
    time.setTimestamp(QDateTime::currentDateTime().toSecsSinceEpoch());
    return time;
}

QString DateTime::toIsoDate()
{
    return QDateTime::fromSecsSinceEpoch(this->getTimestamp()).toString("yyyy-MM-dd");

}

DateTime DateTime::fromIsoDate(QString isoDate)
{
    DateTime dt;
    auto ts = QDateTime::fromString(isoDate,"yyyy-MM-dd").toSecsSinceEpoch();
    dt.setTimestamp(ts);
    return dt;
}

void DateTime::registerMetaType()
{
    if(QMetaType::hasRegisteredConverterFunction<DateTime,QString>())
        return;

    qRegisterMetaType<DateTime>();

    QMetaType::registerConverter<DateTime,QString>([=](DateTime dateTime) -> QString{
        return QString::number(dateTime.getTimestamp());
    });

    QMetaType::registerConverter<QString,DateTime>([=](QString dateTime) -> DateTime{
        DateTime dt;
        dt.setTimestamp(dateTime.toInt());
        return dt;
    });

    QMetaType::registerConverter<DateTime,QJsonValue>([=](DateTime dateTime) -> QJsonValue{
        return QString::number(dateTime.getTimestamp());
    });

    QMetaType::registerConverter<QJsonValue,DateTime>([=](QJsonValue dateTime) -> DateTime{
        DateTime dt;
        dt.setTimestamp(dateTime.toInt());
        return dt;
    });
}
