#ifndef DOUBLE_H
#define DOUBLE_H
#include <QtCore>

/**
 * @brief The Double struct - AspectsPro Double.
 * qint64 2500 == double 25.00, converts double to two decimal places.
 */
struct Double{

    Q_GADGET
    Q_PROPERTY(qint64 asInt READ getValue WRITE setValue)
    Q_PROPERTY(double asDouble READ _intToDouble)
    Q_PROPERTY(QString formatted READ getFormatted WRITE setFormatted)

public:
    Double();
    Double(qint64 value);
//    Double(double value);
    Double(QString doubleString);

    void registerConverter();

    qint64 _doubleToInt(double value);
    double _intToDouble();

    qint64 getValue() const;
    void setValue(qint64 value);

    bool operator==(const Double &d);

    QString getFormatted();
    void setFormatted(QString formatted);

private:
    qint64 value;
};

Q_DECLARE_METATYPE(Double)

#endif // DOUBLE_H
