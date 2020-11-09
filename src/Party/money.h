#ifndef MONEY_H
#define MONEY_H

#include <QtCore>

class Money
{

    Q_GADGET
    Q_PROPERTY(QString formatted READ asString)
    Q_PROPERTY(int raw READ asInt)
public:
    Money();
    Money(int value);
    Money(QVariant value);
    Money(QString intAsString);


    /**
     * @brief getValue
     * @return - Returns int value of money
     */
    Q_INVOKABLE int asInt() const;

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
    Q_INVOKABLE bool operator ==(int value);
    Money operator +=(const Money money);

    Q_INVOKABLE void operator=(int value);
    Q_INVOKABLE operator int();
    /**
     * @brief operator QVariant - Returns int value when returning Variant. Returns QVariant::fromValue()
     */
    Q_INVOKABLE operator QVariant();
    Q_INVOKABLE void operator=(QVariant &value);
    void operator=(QString value);

    /**
     * @brief unformatMoneyString
     * @param moneyString
     * @return
     */
    Q_INVOKABLE int unformatMoneyString(QString moneyString);

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
    Q_INVOKABLE Money fromInt(int moneyAsInt) const;

private:
    int value = 0;
    void setValue(int value);
    void registerConverters();
};

Q_DECLARE_METATYPE(Money)

class MoneyFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString formatted READ getFormatted WRITE setFormatted NOTIFY formattedChanged)
    Q_PROPERTY(int raw READ getRaw NOTIFY rawChanged)

public:
    MoneyFacade();
    virtual ~MoneyFacade() {}


    QString getFormatted() const;
    void setFormatted(const QString &value);

    int getRaw() const;
    void setRaw(int value);

public slots:
    Money asMoney();
    QString asString();
    Money fromInt(int number);

signals:
    void formattedChanged(QString formatted);
    void rawChanged(int raw);

private:
    QString formatted;
    int raw;
    Money money;
};

#endif // MONEY_H
