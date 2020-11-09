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
    void test_overtimeTable();
    void test_payrate();

    void test_paytype();

private:
    bool keepDB = false;

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
    if(!keepDB){
        module.uninstall();
        module.install();
    }
}

void Test::cleanupTestCase()
{
    if(!keepDB){
        DatabaseSingleton::getInstance()->removeDatabaseFolder();
    }
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
    facade.setFirst_name("greg");
    facade.setLast_name("dillon");
    facade.setAddress("#38");
    facade.setBir_number("887332");
    facade.setNis_number("7764");
    facade.setDate_of_birth(DateTime::fromIsoDate("1993-03-08"));
    facade.setEmail_address("greg@aspectspro.com");
    facade.setPassport_number("PP-89978");
    facade.setTelephone_number("868-269-6529");
    facade.setDate_of_discharge(DateTime::getNow());
    facade.setDate_of_employment(DateTime::getNow());
    facade.setDriver_permit_number("DP-09");
    facade.setIdentification_number("id-88373");

    facade.save();

    EmployeeFacade f2;
    f2.setId(facade.getId());
    f2.load();

    QVERIFY(facade.getId() == f2.getId());
    QVERIFY(facade.getFirst_name() == f2.getFirst_name());
    QVERIFY(facade.getLast_name() == f2.getLast_name());
    QVERIFY(facade.getAddress() == f2.getAddress());
    QVERIFY(facade.getBir_number() == f2.getBir_number());
    QVERIFY(facade.getNis_number() == f2.getNis_number());
    QVERIFY(facade.getDate_of_birth() == f2.getDate_of_birth());
    QVERIFY(facade.getEmail_address() == f2.getEmail_address());
    QVERIFY(facade.getPassport_number() == f2.getPassport_number());
    QVERIFY(facade.getTelephone_number() == f2.getTelephone_number());
    QVERIFY(facade.getDate_of_discharge() == f2.getDate_of_discharge());
    QVERIFY(facade.getDate_of_employment() == f2.getDate_of_employment());
    QVERIFY(facade.getDriver_permit_number() == f2.getDriver_permit_number());
    QVERIFY(facade.getIdentification_number() == f2.getIdentification_number());

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

//    s.setAmount(100000);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0);

//    s.setAmount(200000);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0);

//    s.setAmount(300000);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0);

//    s.setAmount(400000);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0);
}

void Test::test_fortnightly_paye()
{
    Salary s({"2020-11-02","2020-11-13"});

//    auto m = 2;
//    s.setAmount(100000);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0*m);

//    s.setAmount(200000*m);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == (15384*m)+1);

//    s.setAmount(300000*m);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == (40384*m)+1);

//    s.setAmount(400000*m);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == (65384*m)+1);
}

void Test::test_monthly_paye()
{
//    Salary s({"2020-11-02","2020-11-27"});

//    auto m = 4;
//    s.setAmount(100000);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 0*m);

//    s.setAmount(200000*m);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 50000);

//    s.setAmount(300000*m);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 150000);

//    s.setAmount(400000*m);
//    QVERIFY(PayeCalculator::getPayeForSalary(s) == 250000);

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

void Test::test_overtimeTable()
{
    OvertimeFacade facade;
    facade.setOvertime_rate_one(2);
    facade.setOvertime_rate_two(2.3);
    facade.setOvertime_rate_three(3);

    qDebug() << facade.getOvertime_rate_one();

    facade.save();
    OvertimeFacade f2;

    QVERIFY(facade.getOvertime_rate_one() == f2.getOvertime_rate_one());
    QVERIFY(facade.getOvertime_rate_two() == f2.getOvertime_rate_two());
    QVERIFY(facade.getOvertime_rate_three() == f2.getOvertime_rate_three());
}

void Test::test_payrate()
{
    PayrateDomainObject pr;
    pr.setId("_test_");
    pr.setPayrate(10000);
    pr.setOvertime_one(15000);
    pr.setOvertime_two(20000);
    pr.setOvertime_three(30000);

    PayrateMapper mp;

    try {
        mp.insert(pr);

        auto pr2 = mp.find( pr.getId());
//        QVERIFY(pr2.getPayrate() == pr.getPayrate());
//        QVERIFY(pr2.getOvertime_one() == pr.getOvertime_one());
//        QVERIFY(pr2.getOvertime_two() == pr.getOvertime_two());
//        QVERIFY(pr2.getOvertime_three() == pr.getOvertime_three());
    } catch (std::exception &e) {
        qInfo() << e.what();
    }

    try {
        PayrateFacade pf;
        pf.setEmployee_id(pr.getId());

//        QVERIFY(pf.getPayrate() == pr.getPayrate());
//        QVERIFY(pf.getOvertime_one() == pr.getOvertime_one());
//        QVERIFY(pf.getOvertime_two() == pr.getOvertime_two());
//        QVERIFY(pf.getOvertime_three() == pr.getOvertime_three());

        pf.setOvertime_one(9000);
        pf.save();
    } catch (std::exception &e) {
        qInfo() << e.what();
    }


}

void Test::test_paytype()
{

    EmployeeFacade emp;
    emp.setFirst_name("Greg");
    emp.setLast_name("Dillon");
    emp.setNis_number("NN-88732");
    emp.setBir_number("BIR-9903");
    emp.save();

    PaytypeFacade pt;
    pt.setId(emp.getId());
    pt.setEmployee_title("Pharmacist");
    pt.save();

    SalaryFacade sl;
    sl.setEmployee_id(emp.getId());
    sl.setGross_salary(1000000);
    sl.setFrom_date(DateTime::fromIsoDate("2020-10-01"));
    sl.setTo_date(DateTime::fromIsoDate("2020-10-20"));
    sl.save();

    SalaryFacade s2;
    s2.setEmployee_id(emp.getId());
    s2.setGross_salary(320000);
    s2.setFrom_date(DateTime::fromIsoDate("2020-10-21"));
    s2.setTo_date(DateTime::fromIsoDate("2020-10-31"));
    s2.save();

    PrinterFacade p;
    p.setSalary_id(s2.getId());
    p.print();
}

QTEST_MAIN(Test)

#include "tst_test.moc"
