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
    Q_PROPERTY(QString formatted READ getFormatted WRITE setFormatted)

public:
    Double();
    Double(int value);
    Double(double value);
    Double(QString doubleString);

    void registerConverter();

    int _doubleToInt(double value);
    double _intToDouble();

    int getValue() const;
    void setValue(int value);

    bool operator==(const Double &d);

    QString getFormatted();
    void setFormatted(QString formatted);

private:
    int value;
};

Q_DECLARE_METATYPE(Double)

#endif // DOUBLE_H
