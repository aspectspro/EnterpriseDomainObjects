#ifndef NAMEINTERFACE_H
#define NAMEINTERFACE_H

#include "../src/EnterpriseDomainObjects.h"

/**
 * @brief The Name_Interface struct
 */
struct Name_Interface : public AbstractDomainObject{


public:
    virtual QString getFirstName() = 0;
    virtual QString getLastName() = 0;
    virtual QString getMiddleName() = 0;

    virtual Name_Interface &setFirstName(QString firstName) = 0;
    virtual Name_Interface &setLastName(QString lastName) = 0;
    virtual Name_Interface &setMiddleName(QString middleName) = 0;

    QString getId(){
        return id;
    }

    Name_Interface& setId(QString id){
        this->id = id;
        return *this;
    }

private:
    QString id;

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

