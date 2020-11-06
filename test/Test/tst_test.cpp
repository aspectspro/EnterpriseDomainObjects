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
    void test_weekly_nis();
    void test_fortnightly_nis();
    void test_monthly_nis();

    void test_weekly_paye();
    void test_fortnightly_paye();
    void test_monthly_paye();

    void test_money();
    void test_salaryDomainObject();
    void test_salaryYearToDate();

    void test_companyInformation();
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

    PartyModule module;
    module.uninstall();
    module.install();
}

void Test::cleanupTestCase()
{
    DatabaseSingleton::getInstance()->removeDatabaseFolder();
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

    PersonMapper mapper;


    person.setFirst_name("Greg");
    person.setLast_name("Dillon");
    person.setPassport_number("5533234");
    person.setDriver_permit_number("55221122");
    person.setIdentification_number("899747397234");
    person.setAddress("#38 Iere Village Princes Town");
    person.setEmail_address("greg@aspectspro.com");
    person.setTelephone_number("868-269-6529");

    try {
        mapper.insert(person);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    try {
        mapper.update(person);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    mapper.remove(person);
}

void Test::test_employee()
{

    EmployeeFacade facade;
    auto emp = facade.employeeFactory();

    emp.setFirst_name("Greg");
    emp.setLast_name("Dillon");
    emp.setAddress("38 Iere Village, Princes Town");
    emp.setTelephone_number("868-269-6529");
    emp.setEmail_address("greg@amapgo.com");

    emp.setIdentification_number(QString::number(qrand()));
    emp.setDriver_permit_number(QString::number(qrand()));
    emp.setPassport_number(QString::number(qrand()));

    emp.setDate_of_employment(DateTime::getNow());

    facade.saveEmployee(emp);

    facade.loadEmployees();
}

void Test::test_weekly_nis()
{
    Salary s({"2020-11-02","2020-11-06"});

    auto m = s.getSalaryDates().mondayChecker();
    auto i = 27000;

    s.setAmount(i*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 3570*m);

    auto ii = 39500;
    s.setAmount(ii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 5220*m);

    auto iii = 53000;
    s.setAmount(iii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 6990*m);

    auto iv = 68500;
    s.setAmount(iv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 9030*m);

    auto v = 84500;
    s.setAmount(v*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 11160*m);

    auto vi = 102500;
    s.setAmount(vi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 13530*m);

    auto vii = 121500;
    s.setAmount(vii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 15960*m);

    auto viii = 143900;
    s.setAmount(viii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 18420*m);

    auto ix = 160000;
    s.setAmount(ix*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 21120*m);

    auto x = 181000;
    s.setAmount(x*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 23880*m);

    auto xi = 202500;
    s.setAmount(xi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 26730*m);

    auto xii = 226000;
    s.setAmount(xii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 29820*m);

    auto xiii = 250500;
    s.setAmount(xiii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 33060*m);

    auto xiv = 277500;
    s.setAmount(xiv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 36630*m);

    auto xv = 302900;
    s.setAmount(xv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 39990*m);

    auto xvi = 313800;
    s.setAmount(xvi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 41430*m);

}

void Test::test_fortnightly_nis()
{
    Salary s({"2020-11-02","2020-11-13"});


    auto m = s.getSalaryDates().mondayChecker();

    auto i = 27000;

    s.setAmount(i*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 3570*m);

    auto ii = 39500;
    s.setAmount(ii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 5220*m);

    auto iii = 53000;
    s.setAmount(iii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 6990*m);

    auto iv = 68500;
    s.setAmount(iv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 9030*m);

    auto v = 84500;
    s.setAmount(v*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 11160*m);

    auto vi = 102500;
    s.setAmount(vi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 13530*m);

    auto vii = 121500;
    s.setAmount(vii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 15960*m);

    auto viii = 143900;
    s.setAmount(viii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 18420*m);

    auto ix = 160000;
    s.setAmount(ix*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 21120*m);

    auto x = 181000;
    s.setAmount(x*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 23880*m);

    auto xi = 202500;
    s.setAmount(xi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 26730*m);

    auto xii = 226000;
    s.setAmount(xii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 29820*m);

    auto xiii = 250500;
    s.setAmount(xiii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 33060*m);

    auto xiv = 277500;
    s.setAmount(xiv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 36630*m);

    auto xv = 302900;
    s.setAmount(xv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 39990*m);

    auto xvi = 313800;
    s.setAmount(xvi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 41430*m);
}

void Test::test_monthly_nis()
{
    Salary s({"2020-11-02","2020-11-27"});


    auto m = s.getSalaryDates().mondayChecker();

    auto i = 27000;

    s.setAmount(i*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 3570*m);

    auto ii = 39500;
    s.setAmount(ii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 5220*m);

    auto iii = 53000;
    s.setAmount(iii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 6990*m);

    auto iv = 68500;
    s.setAmount(iv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 9030*m);

    auto v = 84500;
    s.setAmount(v*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 11160*m);

    auto vi = 102500;
    s.setAmount(vi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 13530*m);

    auto vii = 121500;
    s.setAmount(vii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 15960*m);

    auto viii = 143900;
    s.setAmount(viii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 18420*m);


    auto ix = 165000;
    s.setAmount(ix*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 21120*m);

    auto x = 185500;
    s.setAmount(x*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 23880*m);

    auto xi = 207500;
    s.setAmount(xi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 26730*m);

    auto xii = 233000;
    s.setAmount(xii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 29820*m);

    auto xiii = 260500;
    s.setAmount(xiii*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 33060*m);

    auto xiv = 285000;
    s.setAmount(xiv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 36630*m);

    auto xv = 322900;
    s.setAmount(xv*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 39990*m);

    auto xvi = 353800;
    s.setAmount(xvi*m);
    QVERIFY(NisCalculator::getNisForSalary(s) == 41430*m);
}

void Test::test_weekly_paye()
{
    Salary s({"2020-11-02","2020-11-06"});

    s.setAmount(100000);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0);

    s.setAmount(200000);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 15384);

    s.setAmount(300000);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 40384);

    s.setAmount(400000);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 65384);
}

void Test::test_fortnightly_paye()
{
    Salary s({"2020-11-02","2020-11-13"});

    auto m = 2;
    s.setAmount(100000);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0*m);

    s.setAmount(200000*m);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == (15384*m)+1);

    s.setAmount(300000*m);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == (40384*m)+1);

    s.setAmount(400000*m);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == (65384*m)+1);
}

void Test::test_monthly_paye()
{
    Salary s({"2020-11-02","2020-11-27"});

    auto m = 4;
    s.setAmount(100000);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0*m);

    s.setAmount(200000*m);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 50000);

    s.setAmount(300000*m);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 150000);

    s.setAmount(400000*m);
    QVERIFY(PayeCalculator::getPayeForSalary(s) == 250000);

}

void Test::test_money()
{
    Money money(100099);

    money = 8856000;

    auto str = money.asString();
    QVERIFY("$88,560.00" == str);
    QVERIFY(money.unformatMoneyString(str) == 8856000);

}

void Test::test_salaryDomainObject()
{
    Employee e;
    e.generateId();
    e.setFirst_name("Greg");
    e.setLast_name("Dillon");

    SalaryFacade facade;
    facade.setFrom_date(DateTime::fromIsoDate("2020-11-02"));
    facade.setTo_date(DateTime::fromIsoDate("2020-11-27"));
    facade.setGross_salary(650000);
    try {
        facade.pay(e);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    try {
        facade.pay(e);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    try {
        facade.setFrom_date(DateTime::fromIsoDate("2020-11-28"));
        facade.setTo_date(DateTime::fromIsoDate("2020-12-04"));
        facade.pay(e);
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    SalaryYearToDate ytd;
    auto salary = facade.findLastSalaryForEmployee(e.toJsonObject());
    ytd.setSalary(salary);

    qDebug() << ytd.getYearGross().asString() << salary.getGross_pay().asString();


}

void Test::test_salaryYearToDate()
{
    SalaryYearToDate ytd;
    ytd.loadYearToDate();
}

void Test::test_companyInformation()
{
    CompanyInformationFacade company;
    company.setCompany_name("Aspects Pro");
    company.setAddress("#38 Iere Village Princes Town");
    company.setTelephone_number("868-269-6529");
    company.setEmail_address("greg@aspectspro.com");

    company.saveCompanyInformation();

    CompanyInformationFacade loadedCompany;
    loadedCompany.loadCompanyInformation();

    QVERIFY(loadedCompany.getCompany_name() == ("Aspects Pro"));
    QVERIFY(loadedCompany.getAddress() == ("#38 Iere Village Princes Town"));
    QVERIFY(loadedCompany.getTelephone_number() == ("868-269-6529"));
    QVERIFY(loadedCompany.getEmail_address() == ("greg@aspectspro.com"));

}



QTEST_MAIN(Test)

#include "tst_test.moc"
