#include "employeefacade.h"

DomainModelPtr EmployeeFacade::employeeModel = ModelFactory::createModel<Employee>();
EmployeeMapper EmployeeFacade::mapper;

EmployeeFacade::EmployeeFacade(QObject *parent) : QObject(parent)
{
    connect(this,&EmployeeFacade::idChanged,[=](){
        load();
    });

}

QString EmployeeFacade::getId() const
{
    return id;
}

void EmployeeFacade::setId(const QString &value)
{
    id = value;
    emit idChanged(value);
}

QString EmployeeFacade::getFirst_name() const
{
    return first_name;
}

void EmployeeFacade::setFirst_name(const QString &value)
{
    first_name = value;
    emit first_nameChanged(value);
}

QString EmployeeFacade::getLast_name() const
{
    return last_name;
}

void EmployeeFacade::setLast_name(const QString &value)
{
    last_name = value;
    emit last_nameChanged(value);
}

QString EmployeeFacade::getTelephone_number() const
{
    return telephone_number;
}

void EmployeeFacade::setTelephone_number(const QString &value)
{
    telephone_number = value;
    emit telephone_numberChanged(value);
}

QString EmployeeFacade::getAddress() const
{
    return address;
}

void EmployeeFacade::setAddress(const QString &value)
{
    address = value;
    emit addressChanged(value);
}

QString EmployeeFacade::getEmail_address() const
{
    return email_address;
}

void EmployeeFacade::setEmail_address(const QString &value)
{
    email_address = value;
    emit email_addressChanged(value);
}

QString EmployeeFacade::getIdentification_number() const
{
    return identification_number;
}

void EmployeeFacade::setIdentification_number(const QString &value)
{
    identification_number = value;
    emit identification_numberChanged(value);
}

QString EmployeeFacade::getDriver_permit_number() const
{
    return driver_permit_number;

}

void EmployeeFacade::setDriver_permit_number(const QString &value)
{
    driver_permit_number = value;
    emit driver_permit_numberChanged(value);
}

QString EmployeeFacade::getPassport_number() const
{
    return passport_number;
}

void EmployeeFacade::setPassport_number(const QString &value)
{
    passport_number = value;
    emit passport_numberChanged(value);
}

DateTime EmployeeFacade::getDate_of_birth() const
{
    return date_of_birth;
}

void EmployeeFacade::setDate_of_birth(const DateTime &value)
{
    date_of_birth = value;
    emit date_of_birthChanged(value);
}

QString EmployeeFacade::getBir_number() const
{
    return bir_number;
}

void EmployeeFacade::setBir_number(const QString &value)
{
    bir_number = value;
    emit bir_numberChanged(value);
}

QString EmployeeFacade::getNis_number() const
{
    return nis_number;
}

void EmployeeFacade::setNis_number(const QString &value)
{
    nis_number = value;
    emit nis_numberChanged(value);
}

DateTime EmployeeFacade::getDate_of_employment() const
{
    return date_of_employment;
}

void EmployeeFacade::setDate_of_employment(const DateTime &value)
{
    date_of_employment = value;
    emit date_of_employmentChanged(value);
}

DateTime EmployeeFacade::getDate_of_discharge() const
{
    return date_of_discharge;
}

void EmployeeFacade::setDate_of_discharge(const DateTime &value)
{
    date_of_discharge = value;
    emit date_of_dischargeChanged(value);
}

//QString id,first_name,last_name,telephone_number,address,email_address;
//QString identification_number, driver_permit_number,passport_number;
//DateTime date_of_birth;
//QString bir_number,nis_number;
//DateTime date_of_employment,date_of_discharge;

void EmployeeFacade::save()
{
    Employee emp;
    emp.setId(getId());
    emp.setFirst_name(getFirst_name());
    emp.setLast_name(getLast_name());
    emp.setTelephone_number(getTelephone_number());
    emp.setAddress(getAddress());
    emp.setEmail_address(getEmail_address());
    emp.setIdentification_number(getIdentification_number());
    emp.setDriver_permit_number(getDriver_permit_number());
    emp.setPassport_number(getPassport_number());
    emp.setDate_of_birth(getDate_of_birth());
    emp.setBir_number(getBir_number());
    emp.setNis_number(getNis_number());
    emp.setDate_of_employment(getDate_of_employment());
    emp.setDate_of_discharge(getDate_of_discharge());

    try {
        if(emp.getId() == ""){
            emp.generateId();
            this->id = emp.getId();

            mapper.insert(emp);
        }else{
            mapper.update(emp);
        }

        emit employeeSavedChanged(emp);

    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << "Could not update or create employee";
    }

}

void EmployeeFacade::load()
{
    try {
        auto emp = mapper.find(getId());
        setFirst_name(emp.getFirst_name());
        setLast_name(emp.getLast_name());
        setTelephone_number(emp.getTelephone_number());
        setAddress(emp.getAddress());
        setEmail_address(emp.getEmail_address());
        setIdentification_number(emp.getIdentification_number());
        setDriver_permit_number(emp.getDriver_permit_number());
        setPassport_number(emp.getPassport_number());
        setDate_of_birth(emp.getDate_of_birth());
        setBir_number(emp.getBir_number());
        setNis_number(emp.getNis_number());
        setDate_of_employment(emp.getDate_of_employment());
        setDate_of_discharge(emp.getDate_of_discharge());

    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << QString("Could not load Employee with id '%1'").arg(getId());
    }

}


QAbstractItemModel *EmployeeFacade::getEmployeeModel()
{
    return employeeModel.get();
}

void EmployeeFacade::loadEmployees()
{
    try {
        auto all = mapper.loadAll();
        DomainObjectListPtr data = std::make_shared<QList<DomainObjectPtr>>();

        foreach (auto i, all) {
            data->append(i.clone());
        }

        employeeModel->changeDomainList(data);
    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << e.what();
    }
}
