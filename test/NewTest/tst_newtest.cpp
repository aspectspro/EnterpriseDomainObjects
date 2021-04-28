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
    DatabaseSingleton::getInstance()->initializeDatabase();

    Core core;
    core.initializeCoreTables();
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


    Person p;
    p.setFirst_name("Greg");
    p.setLast_name("Dillon");

    QString className = "Todo";
    ParseCreateObject createApi(configuration);
    auto reply = createApi.createObject(className,p);

    for(int i = 0; i < 1000; i++){
        p.setFirst_name(p.getFirst_name().append(i));
        qDebug() << createApi.createObject(className,p);
    }



//    QSignalSpy spy(reply, &QNetworkReply::finished);

//    QString obj;

//    connect(reply,&QNetworkReply::finished,[&obj,reply](){

//        auto doc = QJsonDocument::fromJson(reply->readAll());
//        ParseCreateResponse created;
//        created.fromJson(doc.object());

//        obj = created.getObjectId();

//        qDebug() << created.toJsonObject();
//    });

//    spy.wait();


//    ParseGetObject get(configuration);

//    auto getReply = get.getObject(className,obj);

//    QSignalSpy spy2(getReply,&QNetworkReply::finished);

//    connect(getReply,&QNetworkReply::finished,[getReply](){

//        qDebug() << getReply->readAll();
//    });

//    spy2.wait();

}


QTEST_MAIN(NewTest)

#include "tst_newtest.moc"
