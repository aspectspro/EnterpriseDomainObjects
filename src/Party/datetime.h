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

private:
    int timestamp = 0;
    void registerMetaType();
};
Q_DECLARE_METATYPE(DateTime)

#endif // DATETIME_H
