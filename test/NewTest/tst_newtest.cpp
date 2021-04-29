#include <QtTest>
#include <QCoreApplication>
#include "../src/EnterpriseDomainObjects.h"
#include "employee_v_1.h"
#include "Parse/Parse.h"
#include <QtNetwork>
#include <QtWebSockets/QWebSocket>
#include <QThread>

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

private:
    std::unique_ptr<SetupModule> module = std::unique_ptr<SetupModule>(new PartyModule());

};

NewTest::NewTest()
{

}

NewTest::~NewTest()
{

}

void NewTest::initTestCase()
{
//    DatabaseSingleton::getInstance()->initializeDatabase();

//    Core core;
//    core.initializeCoreTables();
}

void NewTest::cleanupTestCase()
{

}

void NewTest::tst_partyModule()
{

}

struct ParsePersonMapper : public ParseMapper{

    // ParseMapper interface
public:
    virtual QString className() override;
};

QString ParsePersonMapper::className()
{
    return "People";
}



void NewTest::tst_abstractParty()
{
    auto configuration = ParseConfiguration::getInstance();

    configuration->setServerDomain("localhost")
            .setPort(1337)
            .setMountPath("/parse")
            .setApplicationId("myAppId")
            .setClientKey("customer")
            .setRestApiKey("rest");


    ParsePerson person;
    person.setFirstName("Greg");
    person.setLastName("Dillon");
    person.setMiddleName("DR");

    try {

        ParsePersonMapper mapper;
        mapper.postObject(person);

        auto pers = mapper.getObject<ParsePerson>(person.getObjectId());

        QVERIFY(*pers == person);

        QThread::sleep(5);

        pers->setFirstName("Emma");
        pers->setLastName("Watson-Dillon");

        mapper.putObject(*pers);

        mapper.deleteObject(pers->getObjectId());


    } catch (std::exception &e) {
        qInfo() << e.what();


    }

}


QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
