#include "double.h"

Double::Double(){
    registerConverter();
}

Double::Double(int value) : Double(){
    setValue(value);
}

Double::Double(double value) : Double(){
    setValue(_doubleToInt(value));
}

void Double::registerConverter(){

    if(QMetaType::hasRegisteredConverterFunction<QString,Double>())
        return;

    QMetaType::registerConverter<Double, QString>([](Double value) -> QString{
        return QString::number(value.getValue());
    });

    QMetaType::registerConverter<QString, Double>([](QString value)-> Double{
        Double d(value.toInt());
        return d;
    });

    QMetaType::registerConverter<Double, QJsonValue>([](Double value) -> QJsonValue{
        return QString::number(value.getValue());
    });

}

int Double::_doubleToInt(double value){
    QString v = QString::number(value,'f',2);
    return v.remove(".").toInt();
}

double Double::_intToDouble(){
    auto v = QString::number(getValue());

    int decimalPoint = v.length()-2;
    return v.insert(decimalPoint,".").toDouble();
}

int Double::getValue() const
{
    return value;
}

void Double::setValue(int value)
{
    this->value = value;
}
