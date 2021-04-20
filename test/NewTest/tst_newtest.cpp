#include <QtTest>
#include <QCoreApplication>
#include "../src/EnterpriseDomainObjects.h"
#include "employee_v_1.h"

// add necessary includes here

class NewTest : public QObject
{
    Q_OBJECT

public:
    NewTest();
    ~NewTest();

private slots:
    void initTestCase();
    void cleanupTestCase();    
    void tst_partyModule();
    void tst_abstractParty();

};

NewTest::NewTest()
{

}

NewTest::~NewTest()
{

}

void NewTest::initTestCase()
{
    DatabaseSingleton::getInstance()->initializeDatabase();

    Core core;
    core.initializeCoreTables();
}

void NewTest::cleanupTestCase()
{

}

void NewTest::tst_partyModule()
{
    auto module = std::unique_ptr<SetupModule>(new PartyModule());
    module->install();
}

void NewTest::tst_abstractParty()
{
    TitleMr_ConcreteFactory titleMr;
    TitleMrs_ConcreteFactory titleMrs;
    TitleMs_ConcreteFactory titleMs;
    TitleDr_ConcreteFactory titleDr;


    Employee_v_1 emp(titleMr, "Greg","Dillon");

    qDebug() << emp.getTitle()->name();
    emp.setTitle(titleMrs);

    qDebug() << emp.getTitle()->name();

    emp.setTitle(titleMs);
    qDebug() << emp.getTitle()->name();

    emp.setTitle(titleDr);
    qDebug() << emp.getTitle()->name();
}

QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
