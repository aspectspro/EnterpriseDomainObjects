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
    void tst_titleSuffix();
    void tst_titlePrefix();

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
    FullName_ConcreteBuilder fullNameBuilder;
    UuidIdentifier_ConcreteBuilder uuidBuilder;

    TitlePrefix_ConcreteBuilder prefixBuilder;
    FullNameTitle_ConcreteBuilder fullNameTitleBuilder;

    fullNameTitleBuilder
            .setPrefix(prefixBuilder.mrs())
            .setFirstName("Emma")
            .setLastName("Watson-Dillon");

    QVERIFY(fullNameTitleBuilder.build()->asString() == "Mrs Emma Watson-Dillon");

}

void NewTest::tst_titleSuffix()
{
    TitleSuffix_ConcreteBuilder suffix;
    QVERIFY(suffix.jr().build()->asString() == "Jr");
    QVERIFY(suffix.sr().build()->asString() == "Sr");
}

void NewTest::tst_titlePrefix()
{
    TitlePrefix_ConcreteBuilder prefix;
    QVERIFY(prefix.dr().build()->asString() == "Dr");
    QVERIFY(prefix.mr().build()->asString() == "Mr");
    QVERIFY(prefix.ms().build()->asString() == "Ms");
    QVERIFY(prefix.mrs().build()->asString() == "Mrs");
}

QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
