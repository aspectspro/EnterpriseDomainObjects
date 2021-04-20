#ifndef EMPLOYEE_V_1_H
#define EMPLOYEE_V_1_H

#include "../src/EnterpriseDomainObjects.h"
#include "Title/Title.h"
#include "Name/Name.h"


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

    Employee_v_1 &setName(NameBuilder& builder){
        this->_name = builder.build();
        return *this;
    }

    QString printName(){
        auto _pr = QString("%1 %2").arg(title->name()).arg(_name->printName());
        return _pr;
    }

private:
    Title title;
    std::unique_ptr<Name_Interface> _name;
};

class Employee_v_1_Mapper{

public:
    virtual void insert(Employee_v_1 &employee) = 0;
    virtual void remove(Employee_v_1 &employee) = 0;
    virtual void update(Employee_v_1 &employee) = 0;

};


#endif // EMPLOYEE_V_1_H
