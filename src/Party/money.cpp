#include "money.h"

Money::Money()
{
    registerConverters();
    setValue(0);
}

Money::Money(int value)
{
    registerConverters();
    setValue(value);
}

Money::Money(QVariant value)
{
    registerConverters();
    setValue(value.toInt());
}

Money::Money(QString intAsString)
{
    registerConverters();
    setValue(intAsString.toInt());
}

int Money::asInt() const
{
    return value;
}

QString Money::asString() const
{
    auto amount = asInt();
    auto money = QString::number(amount);
    int decimalPosition = 2;

    if(amount <= 9 && 0 <= amount){
        money = money.prepend("00");
    }
    else if (amount <= 99 && 10 <= amount) {
        money = money.prepend("0");
    }

    money = money.insert(money.count()-decimalPosition,".");


    auto idx = money.indexOf(".");

    QList<int> commaIndices;

    for(int i = idx, q = 0; 0 <= i ; i-- , q++){
        if(q/3 == 1 && q != 0 && i != 0){
            commaIndices << i;
            q = 0;
        }
    }

    foreach (auto i, commaIndices) {
        money.insert(i,",");
    }

    return money.prepend("$");
}

Money Money::operator*(Money &money)
{
    return Money(money.asInt()*asInt());
}

Money Money::operator +(Money &money)
{
    return Money(asInt()+money.asInt());
}

Money Money::operator -(Money &money)
{
    return Money(asInt()-money.asInt());
}

Money Money::operator /(Money &money)
{
    return Money(asInt()/money.asInt());
}

bool Money::operator ==(Money money)
{
    return asInt() == money.asInt();
}

bool Money::operator ==(int value)
{
    return asInt() == value;
}

Money Money::operator +=(const Money money)
{
    auto value = asInt()+money.asInt();
    return value;
}

void Money::operator=(int value){
    this->setValue(value);
}

int Money::unformatMoneyString(QString moneyString)
{
    auto digits = moneyString.remove("$").remove(".").remove(",");
    return digits.toInt();
}

Money::operator QVariant()
{
    return QVariant::fromValue(*this);
}

void Money::operator=(QVariant &value)
{
    setValue(value.toInt());
}

void Money::operator=(QString value)
{
    auto i = value.toInt();
    setValue(i);
}

Money::operator int() { return asInt(); }

void Money::setValue(int value)
{
    this->value = value;
}

void Money::registerConverters()
{
    if(!QMetaType::hasRegisteredConverterFunction<Money,QString>()){
            QMetaType::registerConverter(&Money::intAsString);
            QMetaType::registerConverter(&Money::toJsonValue);

            QMetaType::registerConverter<int,Money>([](int asInt)-> const Money{
                return Money(asInt);
            });

            QMetaType::registerConverter<QString,Money>([](QString fromIntString)-> const Money{
                return Money(fromIntString);
            });

            QMetaType::registerConverter<double,Money>([](double fromDouble)->const Money{
                Money m(static_cast<int>(fromDouble));
                return m;
            });

            QMetaType::registerConverter<Money,double>([](Money money)-> double const{
                return money.asInt();
            });

            qRegisterMetaType<Money>("Money");
    }
}

QString Money::intAsString() const
{
    return QString::number(asInt());
}

QJsonValue Money::toJsonValue() const
{
    return QJsonValue(asInt());
}

Money Money::fromInt(int moneyAsInt) const
{
    return Money(moneyAsInt);
}

