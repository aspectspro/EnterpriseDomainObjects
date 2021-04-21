#ifndef UUIDIDENTIFIER_H
#define UUIDIDENTIFIER_H

#include "IdentifierInterface.h"

/**
 * @brief The UuidIdentifier_Concrete struct
 */
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

/**
 * @brief The UuidIdentifier_ConcreteFactory struct
 */
struct UuidIdentifier_ConcreteFactory : public Identifier_FactoryInterface{
    // Identifier_FactoryInterface interface
public:
    virtual Identifier create() override
    {
        return std::make_unique<UuidIdentifier_Concrete>();
    }
};

/**
 * @brief The UuidIdentifier_ConcreteBuilder struct
 */
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

#endif // UUIDIDENTIFIER_H
