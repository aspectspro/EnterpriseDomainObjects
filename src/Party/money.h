#ifndef MONEY_H
#define MONEY_H

#include <QtCore>

class Money
{

    Q_GADGET
    Q_PROPERTY(QString formatted READ asString)
    Q_PROPERTY(qint64 raw READ asInt)
public:
    Money();
    Money(qint64 value);
    Money(QVariant value);
    Money(QString intAsString);



    /**
     * @brief getValue
     * @return - Returns qint64 value of money
     */
    Q_INVOKABLE qulonglong asInt() const;

    /**
     * @brief getValueAsString - Converts money as currency string
     * @return
     */
    Q_INVOKABLE QString asString() const;

    Q_INVOKABLE Money operator *(Money &money);
    Q_INVOKABLE Money operator +(Money &money);
    Q_INVOKABLE Money operator -(Money &money);
    Q_INVOKABLE Money operator /(Money &money);
    Q_INVOKABLE bool operator ==(Money money);
    Q_INVOKABLE bool operator ==(qint64 value);
    Money operator +=(const Money money);

    Q_INVOKABLE void operator=(qint64 value);
    Q_INVOKABLE operator qint64();
    /**
     * @brief operator QVariant - Returns qint64 value when returning Variant. Returns QVariant::fromValue()
     */
    Q_INVOKABLE operator QVariant();
    Q_INVOKABLE void operator=(QVariant &value);
    void operator=(QString value);

    /**
     * @brief unformatMoneyString
     * @param moneyString
     * @return
     */
    Q_INVOKABLE qulonglong unformatMoneyString(QString moneyString);

    /**
     * @brief unformatString
     * @param moneyString
     * @return
     */
    Q_INVOKABLE QString unformatString(QString moneyString);;

    /**
     * @brief intAsString
     * @return
     */
    Q_INVOKABLE QString intAsString() const;

    /**
     * @brief toJsonValue
     * @return
     */
    QJsonValue toJsonValue() const;

    /**
     * @brief fromInt
     * @param moneyAsInt
     * @return
     */
    Q_INVOKABLE Money fromInt(qint64 moneyAsInt) const;

private:
    qint64 value = 0;
    void setValue(qint64 value);
    void registerConverters();
};

Q_DECLARE_METATYPE(Money)

class MoneyFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString formatted READ getFormatted WRITE setFormatted NOTIFY formattedChanged)
    Q_PROPERTY(qint64 raw READ getRaw NOTIFY rawChanged)

public:
    MoneyFacade();
    virtual ~MoneyFacade() {}


    QString getFormatted() const;
    void setFormatted(const QString &value);

    qint64 getRaw() const;
    void setRaw(qint64 value);

public slots:
    Money asMoney();
    QString asString();
    Money fromInt(qint64 number);

signals:
    void formattedChanged(QString formatted);
    void rawChanged(qint64 raw);

private:
    QString formatted;
    qulonglong raw;
    Money money;
};

#endif // MONEY_H
