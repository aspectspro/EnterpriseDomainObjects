#include <QtTest>
#include <QCoreApplication>
#include "EnterpriseDomainObjects.h"
// add necessary includes here

class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_party();
    void test_person();
    void test_employee();
};

Test::Test()
{

}

Test::~Test()
{

}

void Test::initTestCase()
{
    DatabaseSingleton::getInstance()->initializeDatabase();
    Core core;
    core.initializeCoreTables();

    PartyModule module;
    module.uninstall();
    module.install();
}

void Test::cleanupTestCase()
{
    DatabaseSingleton::getInstance()->removeDatabaseFolder();
}

void Test::test_party()
{
    PartyFacade facade;

    Organization org;
    org.generateId();
    org.setCompany_name("Aspects Pro");
    org.setAddress("#38 Iere Village, Naparima Mayaro Road, Princes Town");
    org.setEmail_address("greg@aspectspro.com");
    org.setTelephone_number("868-269-6529");    

    OrganizationMapper mapper;
    try {
        qDebug() << mapper.loadAll().first().toJsonObject();
    } catch (std::exception &e) {
        qInfo() << e.what();
    }
}

void Test::test_person()
{
    Person person;
    person.generateId();
    person.setDate_of_birth(DateTime::getNow());

    PersonMapper mapper;
    mapper.insert(person);

    person.setFirst_name("Greg");
    person.setLast_name("Dillon");
    person.setPassport_number("5533234");
    person.setDriver_permit_number("55221122");
    person.setIdentification_number("899747397234");
    person.setAddress("#38 Iere Village Princes Town");
    person.setEmail_address("greg@aspectspro.com");
    person.setTelephone_number("868-269-6529");

    try {
        mapper.update(person);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    mapper.remove(person);
}

void Test::test_employee()
{

    EmployeeFacade facade;
    auto emp = facade.employeeFactory();

    emp.setFirst_name("Greg");
    emp.setLast_name("Dillon");
    emp.setAddress("38 Iere Village, Princes Town");
    emp.setTelephone_number("868-269-6529");
    emp.setEmail_address("greg@amapgo.com");

    emp.setIdentification_number(QString::number(qrand()));
    emp.setDriver_permit_number(QString::number(qrand()));
    emp.setPassport_number(QString::number(qrand()));

    emp.setDate_of_employment(DateTime::getNow());

    facade.saveEmployee(emp);

    facade.loadEmployees();
}

QTEST_MAIN(Test)

#include "tst_test.moc"
