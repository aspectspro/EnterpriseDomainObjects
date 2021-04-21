#ifndef FULLNAME_H
#define FULLNAME_H
#include "NameInterface.h"

/**
 * @brief The FullName_Concrete struct
 */
struct FullName_Concrete : public Name_Interface{

    // Name_Interface interface
public:
    virtual QString asString() override;

    FullName_Concrete &setFirstName(QString firstName);

    FullName_Concrete &setLastName(QString lastName);

    FullName_Concrete &setMiddleName(QString middleName);

    QString getFirstName() const;

    QString getLastName() const;

    QString getMiddleName() const;
};

/**
 * @brief The FullName_ConcreteFactory struct
 */
struct FullName_ConcreteFactory : public Name_FactoryInterface{
    // Name_FactoryInterface interface
public:
    virtual Name create() override;
};


/**
 * @brief The ConcreteBuilder struct
 */
struct FullName_ConcreteBuilder : public NameBuilder_Interface{

    // NameBuilder interface
public:
    FullName_ConcreteBuilder();
    FullName_ConcreteBuilder(QString firstName, QString lastName, QString middleName = "");

    FullName_ConcreteBuilder& from(Name &name){
        auto _temp = dynamic_cast<FullName_Concrete*>(name.get());
        setFirstName(_temp->getFirstName());
        setLastName(_temp->getLastName());
        setMiddleName(_temp->getMiddleName());

        return *this;
    }

    FullName_ConcreteBuilder& setFirstName(QString firstName = "");

    FullName_ConcreteBuilder& setMiddleName(QString middleName = "");

    FullName_ConcreteBuilder& setLastName(QString lastName = "");

    // NameBuilder_Interface interface
public:
    virtual NameBuilder_Interface &initializeFactory() override;
};


#endif // FULLNAME_H
