#ifndef DOUBLE_H
#define DOUBLE_H
#include <QtCore>

/**
 * @brief The Double struct - AspectsPro Double.
 * Int 2500 == double 25.00, converts double to two decimal places.
 */
struct Double{

    Q_GADGET
    Q_PROPERTY(int asInt READ getValue WRITE setValue)
    Q_PROPERTY(double asDouble READ _intToDouble)

public:
    Double();
    Double(int value);
    Double(double value);

    void registerConverter();

    int _doubleToInt(double value);
    double _intToDouble();

    int getValue() const;
    void setValue(int value);

    bool operator==(const Double &d);

private:
    int value;
};

Q_DECLARE_METATYPE(Double)

#endif // DOUBLE_H
