#ifndef NAMEINTERFACE_H
#define NAMEINTERFACE_H

#include "../src/EnterpriseDomainObjects.h"



/**
 * @brief The Name_Interface struct
 */
struct Name_Interface{

public:
    /**
     * @brief printName - Prints name to string.
     * @return
     */
    virtual QString asString() = 0;

protected:
    QHash<QString, QString> _data;

};

typedef std::unique_ptr<Name_Interface> Name;

/**
 * @brief The Name_FactoryInterface struct
 */
struct Name_FactoryInterface{

public:
    virtual std::unique_ptr<Name_Interface> create() = 0;

};

typedef std::unique_ptr<Name_FactoryInterface> NameFactory;

/**
 * @brief The NameBuilder struct
 */
struct NameBuilder{

public:
    /**
     * @brief reset - Resets builder product.
     * @return
     */
    virtual NameBuilder& reset() = 0;

    /**
     * @brief build - Builds product as unique_ptr, remember to call std::move(unique_ptr);
     * @return
     */
    virtual Name build() = 0;

};

#endif // NAMEINTERFACE_H
