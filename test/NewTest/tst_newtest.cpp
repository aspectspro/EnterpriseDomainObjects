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
    FullName_ConcreteBuilder fullNameBuilder;
    UuidIdentifier_ConcreteBuilder uuidBuilder;

    TitlePrefix_ConcreteBuilder prefixBuilder;
    FullNameTitle_ConcreteBuilder fullNameTitleBuilder;

    fullNameTitleBuilder
            .setPrefix(prefixBuilder.mrs())
            .setFirstName("Emma")
            .setLastName("Watson-Dillon");

    qDebug() << fullNameTitleBuilder.build()->asString();

    auto _newName = fullNameBuilder
            .setLastName("Dillon")
            .setFirstName("Greg")
            .build();

    auto _me = fullNameTitleBuilder
            .from(_newName)
            .setPrefix(prefixBuilder.mr())
            .build();

    FullNameTitle_Concrete withoutTitle;
    withoutTitle.setFirstName("Georgia").setLastName("Dillon").setMiddleName("Eloise");
    qDebug() << withoutTitle.asString();

    auto withoutTitle2 = fullNameTitleBuilder
            .setFirstName("Greyson")
            .setLastName("Dillon")
            .setMiddleName("Enzo")
            .build();

    qDebug() << withoutTitle2->asString();

    qDebug() << _me->asString();
}

QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
