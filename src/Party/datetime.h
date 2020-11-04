#ifndef DATETIME_H
#define DATETIME_H
#include <QtCore>

class DateTime{

    Q_GADGET
    Q_PROPERTY(int timestamp READ getTimestamp WRITE setTimestamp)
public:
    DateTime();
    Q_INVOKABLE int getTimestamp() const;
    Q_INVOKABLE void setTimestamp(int value);
    Q_INVOKABLE QString getDateTimeAsString();
    Q_INVOKABLE QString toString();
    Q_INVOKABLE QString toDate();
    Q_INVOKABLE QString toTime();
    Q_INVOKABLE static DateTime getNow();
    Q_INVOKABLE QString toIsoDate(int addDays = 0);
    Q_INVOKABLE static DateTime fromIsoDate(QString isoDate);
    Q_INVOKABLE DateTime setIsoDate(QString isoDate);

private:
    int timestamp = 0;
    void registerMetaType();
};
Q_DECLARE_METATYPE(DateTime)

#endif // DATETIME_H
