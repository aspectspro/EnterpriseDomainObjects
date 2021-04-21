#ifndef FULLNAME_H
#define FULLNAME_H
#include "NameInterface.h"
#include "../Title/Title.h"

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

    virtual FullName_ConcreteBuilder& from(Name &name){
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

/**
 * @brief The TitleName_Concrete struct
 */
struct FullNameTitle_Concrete : public FullName_Concrete{


    // Name_Interface interface
public:
    virtual QString asString() override
    {
        auto _name = this->FullName_Concrete::asString();

        //Checking if _prefix is initialized, prevents nullptr error.
        if(_prefix.get() == nullptr)
            return _name;

        return _name.prepend(getPrefix()->asString().isEmpty() ? "" : getPrefix()->asString().append(" "));
    }

    FullNameTitle_Concrete& setPrefix(TitleBuilder_Interface& prefix){
        this->_prefix = prefix.build();
        return *this;
    }

    Title& getPrefix(){
        return _prefix;
    }

private:
    Title _prefix;

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
        TitlePrefix_ConcreteBuilder builder;

        //Checks if Name is initialized, prevents nullptr error.
        if(_temp != nullptr)
            setPrefix(builder.from(_temp->getPrefix()));

        return *this;
    }

    FullNameTitle_ConcreteBuilder& setPrefix(TitleBuilder_Interface &title){
        auto _temp = dynamic_cast<FullNameTitle_Concrete*>(_name.get());
        _temp->setPrefix(title);
        return *this;
    }
};

#endif // FULLNAME_H
