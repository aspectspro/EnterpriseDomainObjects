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

struct NameBuilder_Interface{

public:
    /**
     * @brief reset - Resets builder Name interface.
     * @return
     */
    virtual NameBuilder_Interface& reset(){
        this->_name = _nameFactory->create();
        return *this;
    };

    /**
     * @brief build - Builds product as unique_ptr, remember to call std::move(unique_ptr);
     * @return
     */
    virtual Name build(){
        auto _temp = std::move(_name);
        reset();
        return _temp;
    };

    /**
      @brief initializeFactory - Initializes Factory; Call from constructor of subclass.
     */

    virtual NameBuilder_Interface& initializeFactory() = 0;

protected:
    Name _name;
    NameFactory _nameFactory;

};

#endif // NAMEINTERFACE_H
