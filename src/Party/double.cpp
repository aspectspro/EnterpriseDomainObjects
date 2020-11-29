#include "double.h"

Double::Double(){
    registerConverter();
}

Double::Double(qint64 value) : Double(){
    setValue(value);
}

//Double::Double(double value) : Double(){
//    setValue(_doubleToInt(value));
//}

Double::Double(QString doubleString)
{
    setValue(_doubleToInt(QString::number(doubleString.toDouble(),'f',2).toDouble()));
}

void Double::registerConverter(){

    if(QMetaType::hasRegisteredConverterFunction<QString,Double>())
        return;

    QMetaType::registerConverter<Double, QString>([](Double value) -> QString{
        return QString::number(value.getValue());
    });

    QMetaType::registerConverter<QString, Double>([](QString value)-> Double{
        Double d(value.toUInt());
        return d;
    });

    QMetaType::registerConverter<Double, QJsonValue>([](Double value) -> QJsonValue{
        return QString::number(value.getValue());
    });

    qRegisterMetaType<Double>("Double");
}

qint64 Double::_doubleToInt(double value){
    QString v = QString::number(value,'f',2);
    return v.remove(".").toInt();
}

double Double::_intToDouble(){
    auto v = QString::number(getValue());

    qint64 decimalPoint = v.length()-2;
    return v.insert(decimalPoint,".").toDouble();
}

qint64 Double::getValue() const
{
    return value;
}

void Double::setValue(qint64 value)
{
    this->value = value;
}

bool Double::operator==(const Double &d)
{
    return (getValue() == d.getValue());
}

QString Double::getFormatted()
{
    QString v = QString::number(getValue());
    if(getValue() >= 0 && getValue() <= 9 ){
        v = v.prepend("0.0");
    }else if(getValue() >= 10 && getValue() <= 99 ){
        v = v.prepend("0.");
    }
    else if(getValue() >= 100){
        v = v.insert(1,".");
    }

    return v;
}

void Double::setFormatted(QString formatted)
{
    if(!formatted.contains(".")){
        formatted.append(".00");
    }
    value = formatted.remove(".").toInt();
}


