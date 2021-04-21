#ifndef EMPLOYEE_V_1_H
#define EMPLOYEE_V_1_H

#include "Title/Title.h"
#include "Name/Name.h"
#include "Identifier/Identifier.h"

/**
 * @brief The Employee_v_1 class
 */
class Employee_v_1
{

public:
    Employee_v_1(Title_FactoryInterface &titleFactory,
                 NameBuilder_Interface& nameBuilder,
                 IdentifierBuilder_Interface& identifierBuilder){

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

    Employee_v_1 &setName(NameBuilder_Interface& builder){
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
