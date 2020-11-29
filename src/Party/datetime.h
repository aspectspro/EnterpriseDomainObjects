#ifndef DATETIME_H
#define DATETIME_H
#include <QtCore>

class DateTime{

    Q_GADGET
    Q_PROPERTY(qint64 timestamp READ getTimestamp WRITE setTimestamp)
public:
    DateTime();
    Q_INVOKABLE qint64 getTimestamp() const;
    Q_INVOKABLE void setTimestamp(qint64 value);
    Q_INVOKABLE QString getDateTimeAsString();
    Q_INVOKABLE QString toString();
    Q_INVOKABLE QString toDate();
    Q_INVOKABLE QString toTime();
    Q_INVOKABLE static DateTime getNow();
    Q_INVOKABLE QString toIsoDate(qint64 addDays = 0);
    Q_INVOKABLE static DateTime fromIsoDate(QString isoDate);
    Q_INVOKABLE DateTime setIsoDate(QString isoDate);

    bool operator==(const DateTime &dt);

private:
    qint64 timestamp = 0;
    void registerMetaType();
};
Q_DECLARE_METATYPE(DateTime)

#endif // DATETIME_H
