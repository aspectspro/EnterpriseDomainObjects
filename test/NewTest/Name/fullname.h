#ifndef FULLNAME_H
#define FULLNAME_H
#include "NameInterface.h"
#include "../Title/Title.h"

/**
 * @brief The FullName_Concrete struct
 */
struct FullName_Concrete : public Name_Interface{

    Q_GADGET
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName)
    Q_PROPERTY(QString middleName READ getMiddleName WRITE setMiddleName)

private:
    QString firstName, lastName, middleName;

    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override
    {
        return this->staticMetaObject;
    }

    // Name_Interface interface
public:
    virtual QString getFirstName() override
    {
        return this->firstName;
    }
    virtual QString getLastName() override
    {
        return this->lastName;
    }
    virtual QString getMiddleName() override
    {
        return this->middleName;
    }

    virtual Name_Interface &setFirstName(QString firstName) override
    {
        this->firstName = firstName;
        return *this;
    }
    virtual Name_Interface &setLastName(QString lastName) override
    {
        this->lastName = lastName;
        return *this;
    }
    virtual Name_Interface &setMiddleName(QString middleName) override
    {
        this->middleName = middleName;
        return *this;
    }
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

    virtual FullName_ConcreteBuilder& from(Name &name){        
        this->_name->fromJson(name->toJsonObject());
        return *this;
    }

    FullName_ConcreteBuilder& setFirstName(QString firstName = "");

    FullName_ConcreteBuilder& setMiddleName(QString middleName = "");

    FullName_ConcreteBuilder& setLastName(QString lastName = "");

    // NameBuilder_Interface interface
public:
    virtual NameBuilder_Interface &initializeFactory() override;
};

/**
 * @brief The TitleName_Concrete struct
 */
struct FullNameTitle_Concrete : public FullName_Concrete{

    Q_GADGET
    Q_PROPERTY(QString prefix READ getPrefix WRITE setPrefix)
    Q_PROPERTY(QString suffix READ getSuffix WRITE setSuffix)


    // Name_Interface interface
public:
    FullNameTitle_Concrete& setPrefix(QString prefix){
        this->prefix = prefix;
        return *this;
    }

    QString getPrefix(){
        return prefix;
    }

    QString getSuffix() const{
        return suffix;
    }

    FullNameTitle_Concrete& setSuffix(const QString &value){
        suffix = value;
        return *this;
    }

private:
    QString prefix;
    QString suffix;


    // AbstractDomainObject interface
public:
    virtual const QMetaObject &metaObject() const override
    {
        return this->staticMetaObject;
    }
};

/**
 * @brief The TItleName_ConcreteFactory struct
 */
struct FullNameTitle_ConcreteFactory : public FullName_ConcreteFactory{
    // FullName_Concrete_FactoryInterface interface
public:
    virtual Name create() override
    {
        return std::make_unique<FullNameTitle_Concrete>();
    }
};

struct FullNameTitle_ConcreteBuilder : public FullName_ConcreteBuilder{

    // NameBuilder_Interface interface
public:
    FullNameTitle_ConcreteBuilder(){
        initializeFactory();
        reset();
    }

    virtual NameBuilder_Interface &initializeFactory() override
    {
        this->_nameFactory = std::make_unique<FullNameTitle_ConcreteFactory>();
        return *this;
    }

    // FullName_ConcreteBuilder interface
public:
    virtual FullNameTitle_ConcreteBuilder &from(Name &name) override
    {
        this->FullName_ConcreteBuilder::from(name);

        auto _temp = dynamic_cast<FullNameTitle_Concrete*>(name.get());

        //Checks if Name is initialized, prevents nullptr error.
        if(_temp != nullptr)
            this->_name->fromJson(_temp->toJsonObject());

        return *this;
    }

    FullNameTitle_ConcreteBuilder& setPrefix(TitleBuilder_Interface &title){
        auto _temp = dynamic_cast<FullNameTitle_Concrete*>(_name.get());
        _temp->setPrefix(title.build()->asString());
        return *this;
    }
};

#endif // FULLNAME_H
