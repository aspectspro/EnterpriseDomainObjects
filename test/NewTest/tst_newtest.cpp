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
    TitleMr_ConcreteFactory Mr;
    TitleMrs_ConcreteFactory Mrs;
    TitleMs_ConcreteFactory Ms;
    TitleDr_ConcreteFactory Dr;

    FullName_ConcreteBuilder nameBuilder;
    UuidIdentifier_ConcreteBuilder uuidBuilder;

    Employee_v_1 emp(Dr,
                     nameBuilder.setFirstName("Greg").setLastName("Dillon").setMiddleName("DR"),
                     uuidBuilder.generateNewId());


    qDebug() << emp.getIdentifier()->asString();
    qDebug() << emp.getTitle()->asString();
    qDebug() << emp.getName()->asString();

    auto _newName = nameBuilder.from(emp.getName()).build();
    QVERIFY(_newName->asString() == emp.getName()->asString());

    auto _newId = uuidBuilder.from(emp.getIdentifier()).build();
    QVERIFY(_newId->asString() == emp.getIdentifier()->asString());

}

QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
