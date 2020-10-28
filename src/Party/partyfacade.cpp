#include "partyfacade.h"

PartyFacade::PartyFacade()
{
    _organizationModel = ModelFactory::createModel<Organization>();
    Core core;
    core.initializeCoreTables();

    PartyModule partyModule;
    partyModule.install();

    DomainObjectListPtr data = std::make_shared<QList<DomainObjectPtr>>();
    _organizationModel->changeDomainList(data);

}

QAbstractItemModel *PartyFacade::organizationModel()
{
    return _organizationModel.get();
}

Organization PartyFacade::createOrganization(QString company_name, QString email_address, QString address, QString telephone_number)
{
    Organization org;
    org.setCompany_name(company_name);
    org.setAddress(address);
    org.setTelephone_number(telephone_number);
    org.setEmail_address(email_address);
    org.generateId();
    return org;

}

void PartyFacade::insert(Organization organization)
{
    _organizationModel->insert(organization.clone());
}

void PartyFacade::save(Organization organization)
{
    OrganizationMapper mapper;
    try {
        mapper.insert(organization);
        insert(organization);
    } catch (std::exception &e) {
        emit error(e.what());
    }
}

void PartyFacade::load()
{
    OrganizationMapper mapper;
    auto all = mapper.loadAll();

    DomainObjectListPtr data = std::make_shared<QList<DomainObjectPtr>>();
    data->clear();

    foreach (auto i, all) {
        data->append(i.clone());
    }
    _organizationModel->changeDomainList(data);

}

EmployeeFacade::EmployeeFacade()
{
    employeeModel = ModelFactory::createModel<Employee>();
}

Employee EmployeeFacade::employeeFactory()
{
    Employee employee;
    employee.generateId();
    return employee;
}

void EmployeeFacade::saveEmployee(Employee employee)
{
    try {
        mapper.insert(employee);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }
}

void EmployeeFacade::removeEmployee(Employee employee)
{
    try {
        mapper.remove(employee);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }
}

void EmployeeFacade::updateEmployee(Employee employee)
{
    try {
        mapper.update(employee);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }
}

QAbstractItemModel *EmployeeFacade::getEmployeeModel()
{
    return this->employeeModel.get();
}

void EmployeeFacade::loadEmployees()
{
    auto all = mapper.loadAll();
    DomainObjectListPtr data = std::make_shared<QList<DomainObjectPtr>>();

    foreach (auto i, all) {
        data->append(i.clone());
    }

    employeeModel->changeDomainList(data);
}

DateTime EnterpriseDateUtils::now(){
    return DateTime::getNow();
}

DateTime EnterpriseDateUtils::dateTimeFromTimestamp(int timestamp){
    DateTime dt;
    dt.setTimestamp(timestamp);
    return dt;
}

DateTime EnterpriseDateUtils::dateTimeFromUtc(QString utcTime){
    auto secs = QDateTime::fromString(utcTime).toSecsSinceEpoch()+43200;
    DateTime dt;
    dt.setTimestamp(secs);
    return dt;
}

QString EnterpriseDateUtils::appDatesView(int timestamp){
    auto dt = QDateTime::fromSecsSinceEpoch(timestamp+43200);
    return dt.toString("dd/MM/yyyy");
}

QString EnterpriseDateUtils::appDatesView(QDateTime dateTime){
    return appDatesView(dateTime.toSecsSinceEpoch());
}
