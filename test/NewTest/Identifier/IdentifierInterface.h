#ifndef IDENTIFIERINTERFACE_H
#define IDENTIFIERINTERFACE_H

#include "../src/EnterpriseDomainObjects.h"

/**
 * @brief The Identifier_Interface struct
 */
struct Identifier_Interface{

public:
    virtual QString asString() const = 0;

protected:
    QString _data;

};

typedef std::unique_ptr<Identifier_Interface> Identifier;

/**
 * @brief The Identifier_FactoryInterface struct
 */
struct Identifier_FactoryInterface{

public:
    virtual Identifier create() = 0;

};

typedef std::unique_ptr<Identifier_FactoryInterface> IdentifierFactory;

/**
 * @brief The IdentifierBuilder_Interface struct - Remember to call initializeFactory then reset in subclass
 * constructor otherwise will throw exception;
 */
struct IdentifierBuilder_Interface{

public:
    /**
     * @brief reset - Resets builder Identifier interface.
     * @return
     */
    virtual IdentifierBuilder_Interface& reset(){
        this->_identifier = _identifierFactory->create();
        return *this;
    };

    /**
     * @brief build - Builds product as unique_ptr, remember to call std::move(unique_ptr);
     * @return
     */
    virtual Identifier build(){
        auto _temp = std::move(_identifier);
        reset();
        return _temp;
    };

    /**
      @brief initializeFactory - Initializes Factory; Call from constructor of subclass.
     */

    virtual IdentifierBuilder_Interface& initializeFactory() = 0;

protected:
    Identifier _identifier;
    IdentifierFactory _identifierFactory;
};

#endif // IDENTIFIERINTERFACE_H
