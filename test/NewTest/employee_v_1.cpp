#include "employee_v_1.h"


QString Employee_v_1::getFirstname() const
{
    return firstname;
}

void Employee_v_1::setFirstname(const QString &value)
{
    firstname = value;
}

QString Employee_v_1::getLastname() const
{
    return lastname;
}

void Employee_v_1::setLastname(const QString &value)
{
    lastname = value;
}
