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
struct FullNameConcreteBuilder : public NameBuilder{

    // NameBuilder interface
public:
    FullNameConcreteBuilder();

    FullNameConcreteBuilder(QString firstName, QString lastName, QString middleName = "");

    virtual Name build() override;

    FullNameConcreteBuilder& setFirstName(QString firstName);

    FullNameConcreteBuilder& setMiddleName(QString middleName);

    FullNameConcreteBuilder& setLastName(QString lastName);

private:
    std::unique_ptr<Name_FactoryInterface> _nameFactory;
    Name _name;

    // NameBuilder interface
public:
    virtual NameBuilder &reset() override;
};


#endif // FULLNAME_H
