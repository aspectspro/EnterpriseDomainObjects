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



void NewTest::tst_abstractParty()
{
    ParseConfiguration configuration;

    configuration.setServerDomain("localhost")
            .setPort(1337)
            .setMountPath("/parse")
            .setApplicationId("myAppId")
            .setClientKey("customer")
            .setRestApiKey("rest");


    ParsePerson person;
    person.setFirstName("Greg");
    person.setLastName("Dillon");
    person.setMiddleName("DR");

    QString className = "People";
    ParsePostObject postObject(configuration);

    try {
        auto reply = postObject.createObject(className,person);


        ParseDeleteObject deleteResource(configuration);
        deleteResource.deleteByObjectId(className,person.getObjectId());

        ParseGetObject getObject(configuration);

        auto _person = getObject.getObject<ParsePerson>(className,person.getObjectId());
        QVERIFY(person == *_person.get());

    } catch (std::exception &e) {
        qInfo() << e.what();


    }

}


QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
