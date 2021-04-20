#ifndef EMPLOYEE_V_1_H
#define EMPLOYEE_V_1_H

#include "../src/EnterpriseDomainObjects.h"
#include "Title/Title.h"


class Employee_v_1
{
public:
    Employee_v_1(Title_FactoryInterface &titleFactory,
                 QString firstname,
                 QString lastname) : firstname(firstname), lastname(lastname){
        setTitle(titleFactory);
    }

    Title& getTitle(){
        return title;
    }

    Employee_v_1 &setTitle(Title_FactoryInterface &titleFactory){
        this->title = titleFactory.create();
        return *this;
    }

    QString getFirstname() const;
    void setFirstname(const QString &value);

    QString getLastname() const;
    void setLastname(const QString &value);

private:
    QString firstname, lastname;
    Title title;
};


#endif // EMPLOYEE_V_1_H
