#include "fullname.h"

QString FullName_Concrete::printName()
{
    auto _fullName = QString("%1%2%3")
            .arg(getFirstName().append(" "))
            .arg(getMiddleName().isEmpty() ? "" : getMiddleName().append(" "))
            .arg(getLastName());

    return _fullName;
}

FullName_Concrete &FullName_Concrete::setFirstName(QString firstName){
    _data.insert("firstName",firstName);
    return *this;
}

FullName_Concrete &FullName_Concrete::setLastName(QString lastName){
    _data.insert("lastName",lastName);
    return *this;
}

FullName_Concrete &FullName_Concrete::setMiddleName(QString middleName){
    _data.insert("middleName",middleName);
    return *this;
}

QString FullName_Concrete::getFirstName() const {
    return _data.value("firstName");
}

QString FullName_Concrete::getLastName() const {
    return _data.value("lastName");
}

QString FullName_Concrete::getMiddleName() const {
    return _data.value("middleName");
}

std::unique_ptr<Name_Interface> FullName_ConcreteFactory::create()
{
    return std::make_unique<FullName_Concrete>();
}

FullNameConcreteBuilder::FullNameConcreteBuilder(){
    _nameFactory = std::make_unique<FullName_ConcreteFactory>();
    reset();
}

FullNameConcreteBuilder::FullNameConcreteBuilder(QString firstName, QString lastName, QString middleName) : FullNameConcreteBuilder(){
    setFirstName(firstName).setLastName(lastName).setMiddleName(middleName);
}

std::unique_ptr<Name_Interface> FullNameConcreteBuilder::build()
{
    auto _copy = std::move(_name);
    reset();
    return _copy;
}

FullNameConcreteBuilder &FullNameConcreteBuilder::setFirstName(QString firstName){
    auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
    fullName->setFirstName(firstName);
    return *this;
}

FullNameConcreteBuilder &FullNameConcreteBuilder::setMiddleName(QString middleName){
    auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
    fullName->setMiddleName(middleName);
    return *this;
}

FullNameConcreteBuilder &FullNameConcreteBuilder::setLastName(QString lastName){
    auto fullName = dynamic_cast<FullName_Concrete*>(_name.get());
    fullName->setLastName(lastName);
    return *this;
}

NameBuilder &FullNameConcreteBuilder::reset()
{
    _name = _nameFactory->create();
    return *this;
}
