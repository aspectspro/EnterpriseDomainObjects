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
    FullName_ConcreteBuilder nameBuilder;
    UuidIdentifier_ConcreteBuilder uuidBuilder;
    TitlePrefix_ConcreteBuilder prefixBuilder;

    TitleName_ConcreteBuilder nameTitleBuilder;

    nameTitleBuilder
            .setTitle(prefixBuilder.mrs())
            .setFirstName("Emma")
            .setLastName("Watson-Dillon");

    qDebug() << nameTitleBuilder.build()->asString();

    auto _newName = nameBuilder
            .setLastName("Dillon")
            .setFirstName("Greg")
            .build();

    auto _ne = nameTitleBuilder
            .from(_newName)
            .setTitle(prefixBuilder.mr())
            .build();

    qDebug() << _ne->asString();
}

QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
