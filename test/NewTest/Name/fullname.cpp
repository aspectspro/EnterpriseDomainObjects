#include "fullname.h"

Name FullName_ConcreteFactory::create()
{
    return std::make_unique<FullName_Concrete>();
}

FullName_ConcreteBuilder::FullName_ConcreteBuilder(){
    initializeFactory();
    reset();
}

FullName_ConcreteBuilder &FullName_ConcreteBuilder::setFirstName(QString firstName){
    auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
    fullName->setFirstName(firstName);
    return *this;
}

FullName_ConcreteBuilder &FullName_ConcreteBuilder::setMiddleName(QString middleName){
    auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
    fullName->setMiddleName(middleName);
    return *this;
}

FullName_ConcreteBuilder &FullName_ConcreteBuilder::setLastName(QString lastName){
    auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
    fullName->setLastName(lastName);
    return *this;
}

NameBuilder_Interface &FullName_ConcreteBuilder::initializeFactory()
{
    this->_nameFactory = std::make_unique<FullName_ConcreteFactory>();
    return *this;
}


