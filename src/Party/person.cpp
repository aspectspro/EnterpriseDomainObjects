#include "person.h"

const QMetaObject &Person::metaObject() const
{
    return staticMetaObject;
}

void Person::registerConverter()
{
    qRegisterMetaType<Person>();
}

QString Person::getFirst_name() const
{
    return first_name;
}

void Person::setFirst_name(const QString value)
{
    first_name = value;
}

QString Person::getLast_name() const
{
    return last_name;
}

void Person::setLast_name(const QString value)
{
    last_name = value;
}

QString Person::getIdentification_number() const
{
    return identification_number;
}

void Person::setIdentification_number(const QString value)
{
    identification_number = value;
}

QString Person::getDriver_permit_number() const
{
    return driver_permit_number;
}

void Person::setDriver_permit_number(const QString value)
{
    driver_permit_number = value;
}

QString Person::getPassport_number() const
{
    return passport_number;
}

void Person::setPassport_number(const QString value)
{
    passport_number = value;
}

DateTime Person::getDate_of_birth() const
{
    return date_of_birth;
}

void Person::setDate_of_birth(const DateTime value)
{
    date_of_birth = value;
}


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

DateTime DateTime::getNow()
{
    DateTime time;
    time.setTimestamp(QDateTime::currentDateTime().toSecsSinceEpoch());
    return time;
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


const QMetaObject &Employee::metaObject() const
{
    return staticMetaObject;
}

void Employee::registerConverter()
{
}

QString Employee::getBir_number() const
{
    return bir_number;
}

void Employee::setBir_number(const QString value)
{
    bir_number = value;
}

QString Employee::getNis_number() const
{
    return nis_number;
}

void Employee::setNis_number(const QString value)
{
    nis_number = value;
}

DateTime Employee::getDate_of_employment() const
{
    return date_of_employment;
}

void Employee::setDate_of_employment(const DateTime value)
{
    date_of_employment = value;
}

DateTime Employee::getDate_of_discharge() const
{
    return date_of_discharge;
}

void Employee::setDate_of_discharge(const DateTime value)
{
    date_of_discharge = value;
}
