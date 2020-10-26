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
}

void Test::cleanupTestCase()
{
//    DatabaseSingleton::getInstance()->removeDatabaseFolder();
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
}

void Test::test_employee()
{

}

QTEST_MAIN(Test)

#include "tst_test.moc"
