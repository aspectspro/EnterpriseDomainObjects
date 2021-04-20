#ifndef EMPLOYEE_V_1_H
#define EMPLOYEE_V_1_H

#include "../src/EnterpriseDomainObjects.h"
#include "Title/Title.h"

/**
 * @brief The Name_Interface struct
 */
struct Name_Interface{

public:
    virtual QString printName() = 0;

protected:
    QHash<QString, QString> _data;

};

/**
 * @brief The Name_FactoryInterface struct
 */
struct Name_FactoryInterface{

public:
    virtual std::unique_ptr<Name_Interface> create() = 0;

};

/**
 * @brief The FullName_Concrete struct
 */
struct FullName_Concrete : public Name_Interface{

    // Name_Interface interface
public:
    virtual QString printName() override
    {
        auto _fullName = QString("%1%2%3")
                .arg(getFirstName().append(" "))
                .arg(getMiddleName().isEmpty() ? "" : getMiddleName().append(" "))
                .arg(getLastName());

        return _fullName;
    }

    FullName_Concrete &setFirstName(QString firstName){
        _data.insert("firstName",firstName);
        return *this;
    }

    FullName_Concrete &setLastName(QString lastName){
        _data.insert("lastName",lastName);
        return *this;
    }

    FullName_Concrete &setMiddleName(QString middleName){
        _data.insert("middleName",middleName);
        return *this;
    }

    QString getFirstName() const {
        return _data.value("firstName");
    }

    QString getLastName() const {
        return _data.value("lastName");
    }

    QString getMiddleName() const {
        return _data.value("middleName");
    }
};

/**
 * @brief The FullName_ConcreteFactory struct
 */
struct FullName_ConcreteFactory : public Name_FactoryInterface{
    // Name_FactoryInterface interface
public:
    virtual std::unique_ptr<Name_Interface> create() override
    {
        return std::make_unique<FullName_Concrete>();
    }
};


/**
 * @brief The NameBuilder struct
 */
struct NameBuilder{

public:
    virtual NameBuilder& reset() = 0;

    virtual std::unique_ptr<Name_Interface> build() = 0;

};

/**
 * @brief The ConcreteBuilder struct
 */
struct FullNameConcreteBuilder : public NameBuilder{

    // NameBuilder interface
public:
    FullNameConcreteBuilder(){
        _nameFactory = std::make_unique<FullName_ConcreteFactory>();
        reset();
    }

    FullNameConcreteBuilder(QString firstName, QString lastName, QString middleName = "") : FullNameConcreteBuilder(){
        setFirstName(firstName).setLastName(lastName).setMiddleName(middleName);
    }

    virtual std::unique_ptr<Name_Interface> build() override
    {
        return std::move(_name);
        reset();
    }

    FullNameConcreteBuilder& setFirstName(QString firstName){
        auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
        fullName->setFirstName(firstName);
        return *this;
    }

    FullNameConcreteBuilder& setMiddleName(QString middleName){
        auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
        fullName->setMiddleName(middleName);
        return *this;
    }

    FullNameConcreteBuilder& setLastName(QString lastName){
        auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
        fullName->setLastName(lastName);
        return *this;
    }

private:
    std::unique_ptr<Name_FactoryInterface> _nameFactory;
    std::unique_ptr<Name_Interface> _name;

    // NameBuilder interface
public:
    virtual NameBuilder &reset() override
    {
        _name = _nameFactory->create();
        return *this;
    }
};


/**
 * @brief The Employee_v_1 class
 */
class Employee_v_1
{
public:
    Employee_v_1(Title_FactoryInterface &titleFactory, NameBuilder& nameBuilder){
        setTitle(titleFactory);
        setName(nameBuilder);
    }

    Title& getTitle(){
        return title;
    }

    Employee_v_1 &setTitle(Title_FactoryInterface &titleFactory){
        this->title = titleFactory.create();
        return *this;
    }

    void setName(NameBuilder& builder){
        this->_name = builder.build();
    }

    QString printName(){
        auto _pr = QString("%1 %2").arg(title->name()).arg(_name->printName());
        return _pr;
    }

private:
    Title title;
    std::unique_ptr<Name_Interface> _name;
};


#endif // EMPLOYEE_V_1_H
