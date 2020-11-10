#include "datetime.h"
DateTime::DateTime()
{
    registerMetaType();
}

qint64 DateTime::getTimestamp() const
{
    return timestamp;
}

void DateTime::setTimestamp(qint64 value)
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

QString DateTime::toIsoDate(qint64 addDays)
{
    return QDateTime::fromSecsSinceEpoch(this->getTimestamp())
            .addDays(addDays)
            .toString("yyyy-MM-dd");

}

DateTime DateTime::fromIsoDate(QString isoDate)
{
    DateTime dt;
    auto ts = QDateTime::fromString(isoDate,"yyyy-MM-dd").toSecsSinceEpoch();
    dt.setTimestamp(ts);
    return dt;
}

DateTime DateTime::setIsoDate(QString isoDate)
{
    setTimestamp(QDateTime::fromString(isoDate,"yyyy-MM-dd").toSecsSinceEpoch());
    return *this;
}

bool DateTime::operator==(const DateTime &dt)
{
    return (getTimestamp() == dt.getTimestamp());
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
