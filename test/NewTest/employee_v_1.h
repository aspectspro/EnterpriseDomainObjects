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
    Employee_v_1(NameBuilder_Interface& nameBuilder,
                 IdentifierBuilder_Interface& identifierBuilder){

        setName(nameBuilder);
        setIdentifier(identifierBuilder);
    }

    Employee_v_1 &setName(NameBuilder_Interface& builder){
        this->_name = builder.build();
        return *this;
    }

    Name& getName(){
        return _name;
    }

    QString printName(){
        return "_pr";
    }

    Employee_v_1 &setIdentifier(IdentifierBuilder_Interface &identifierBuilder){
        this->_id = identifierBuilder.build();
        return *this;
    }

    Identifier& getIdentifier(){
        return this->_id;
    }

private:
    Name _name;
    Identifier _id;
};

class Employee_v_1_Mapper{

public:
    virtual void insert(Employee_v_1 &employee){

    };

    virtual void remove(Employee_v_1 &employee){

    }

    virtual void update(Employee_v_1 &employee){

    };

};


#endif // EMPLOYEE_V_1_H
