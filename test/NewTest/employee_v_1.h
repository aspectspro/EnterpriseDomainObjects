#ifndef EMPLOYEE_V_1_H
#define EMPLOYEE_V_1_H

#include "../src/EnterpriseDomainObjects.h"
#include "Title/Title.h"
#include "Name/Name.h"

struct Identifier_Interface{

public:
    virtual QString asString() const = 0;

protected:
    QString _data;

};

typedef std::unique_ptr<Identifier_Interface> Identifier;

struct Identifier_FactoryInterface{

public:
    virtual Identifier create() = 0;

};

typedef std::unique_ptr<Identifier_FactoryInterface> IdentifierFactory;

struct UuidIdentifier_Concrete: public Identifier_Interface{

    // Identifier_Interface interface
public:
    virtual QString asString() const override
    {
        return this->_data;
    }

    UuidIdentifier_Concrete &setId(QString id){
        this->_data = id;
        return *this;
    }
};

struct UuidIdentifier_ConcreteFactory : public Identifier_FactoryInterface{
    // Identifier_FactoryInterface interface
public:
    virtual Identifier create() override
    {
        return std::make_unique<UuidIdentifier_Concrete>();
    }
};

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

struct UuidIdentifier_ConcreteBuilder : public IdentifierBuilder_Interface{


    // IdentifierBuilder_Interface interface
public:

    UuidIdentifier_ConcreteBuilder(){
        initializeFactory();
        reset();
    }

    /**
     * @brief generateNewId - Call this method to generate new Uuid.
     * @return
     */
    UuidIdentifier_ConcreteBuilder& generateNewId(){
        auto _temp = dynamic_cast<UuidIdentifier_Concrete*>(_identifier.get());

        auto _newId = QUuid::createUuid().toString(QUuid::Id128);
        _temp->setId(_newId);

        return *this;

    }

    /**
     * @brief setId
     * @param id
     * @return
     */
    UuidIdentifier_ConcreteBuilder& setId(QString id){
        auto _temp = dynamic_cast<UuidIdentifier_Concrete*>(_identifier.get());
        _temp->setId(id);
        return *this;
    }

    virtual IdentifierBuilder_Interface &initializeFactory() override
    {
        this->_identifierFactory = std::make_unique<UuidIdentifier_ConcreteFactory>();
        return *this;
    }
};

/**
 * @brief The Employee_v_1 class
 */
class Employee_v_1
{

public:
    Employee_v_1(Title_FactoryInterface &titleFactory, NameBuilder& nameBuilder, IdentifierBuilder_Interface& identifierBuilder){
        setTitle(titleFactory);
        setName(nameBuilder);
        setIdentifier(identifierBuilder);
    }

    Title& getTitle(){
        return _title;
    }

    Employee_v_1 &setTitle(Title_FactoryInterface &titleFactory){
        this->_title = titleFactory.create();
        return *this;
    }

    Employee_v_1 &setName(NameBuilder& builder){
        this->_name = builder.build();
        return *this;
    }

    Name& getName(){
        return _name;
    }

    QString printName(){
        auto _pr = QString("%1 %2").arg(_title->asString()).arg(_name->asString());
        return _pr;
    }

    Employee_v_1 &setIdentifier(IdentifierBuilder_Interface &identifierBuilder){
        this->_id = identifierBuilder.build();
        return *this;
    }

    Identifier& getIdentifier(){
        return this->_id;
    }

private:
    Title _title;
    Name _name;
    Identifier _id;
};

class Employee_v_1_Mapper{

public:
    virtual void insert(Employee_v_1 &employee) = 0;
    virtual void remove(Employee_v_1 &employee) = 0;
    virtual void update(Employee_v_1 &employee) = 0;

};


#endif // EMPLOYEE_V_1_H
