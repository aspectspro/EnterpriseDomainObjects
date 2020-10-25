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
    DatabaseSingleton::getInstance()->removeDatabaseFolder();
}

void Test::test_party()
{
    PartyModule partyModule;
    partyModule.install();

    Organization org;
    org.generateId();
    org.setCompany_name("Aspects Pro");
    org.setAddress("#38 Iere Village, Naparima Mayaro Road, Princes Town");
    org.setEmail_address("greg@aspectspro.com");
    org.setTelephone_number("868-269-6529");

    OrganizationMapper mapper;
    try {
        mapper.insert(org);
        org.setCompany_name("AspectsPro Software");
        org.setAddress("#1 Naparima Mayaro Road, Princes Town");

    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    QList<Organization> all;

    try {
        all = mapper.loadAll();
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    //Step 1 : Call ModelFactory::createModule<Type>() to initialize model;
    auto model = ModelFactory::createModel<Organization>();

    //Step 2 : Initialize DomainObjectPtr list - TODO : automate this.
    DomainObjectListPtr orgList = std::make_shared<QList<DomainObjectPtr>>();
    model->changeDomainList(orgList);

    //Step 3 : Insert Data. TODO : automate this.
    orgList->clear();
    foreach (auto i, all) {
        orgList->append(i.clone());
    }

    partyModule.uninstall();
}

QTEST_MAIN(Test)

#include "tst_test.moc"
