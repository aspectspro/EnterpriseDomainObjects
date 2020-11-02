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
    void test_salary();
};

Test::Test()
{

}

Test::~Test()
{

}

class Salary{


public:
    enum SalaryType{
        Weekly,
        FortNightly,
        Montly
    };

    Salary(SalaryType type){
        this->type = type;
    }

    int amount() const;
    void setAmount(int amount);

    SalaryType getType() const;

private:
    int _amount = 0;
    SalaryType type;
};

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

class SalaryRange{

public:
    SalaryRange(){}
    SalaryRange(int min,int max){
        this->min = min;
        this->max = max;
    }
    int getMin() const;

    int getMax() const;

private:
    int min;
    int max;
};

class NisEarnings{

public:
    NisEarnings(SalaryRange weeklyRange, SalaryRange monthlyRange, int totalWeeklyContribution) :
        weeklyRange(weeklyRange),monthlyRange(monthlyRange), totalWeeklyContribution(totalWeeklyContribution){}

    int getAssumedWeekly() const;
    void setAssumedWeekly(int value);

    int getEmployerWeekly(){
        return getTotalWeeklyContribution()/1.5;
    }

    int getEmployeeWeekly(){
        return getTotalWeeklyContribution()/3;
    }

    int getTotalWeeklyContribution() const;
    void setTotalWeeklyContribution(int value);

    SalaryRange getWeeklyRange() const;

    SalaryRange getMonthlyRange() const;

private:
    SalaryRange weeklyRange;
    SalaryRange monthlyRange;
    int totalWeeklyContribution = 0;
};

class NisChecker{
public:
    NisChecker(){
        NisEarnings i({20000,33999},{86700,147299},3570);
        NisEarnings ii({34000,44999},{147300,194999},5220);
        NisEarnings iii({45000,60999},{195000,264299},6990);
        NisEarnings iv({61000,75999},{264300,329399},9030);
        NisEarnings v({76000,92999},{329300,402999},11160);

        NisEarnings vi({93000,111999},{403000,485299},13530);
        NisEarnings vii({112000,129999},{485300,563299},15960);
        NisEarnings viii({130000,148999},{563300,645699},18420);
        NisEarnings ix({149000,170999},{645700,740999},21120);
        NisEarnings x({171000,190999},{741000,827699},23880);

        NisEarnings xi({191000,213999},{827700,927299},26730);
        NisEarnings xii({214000,237999},{927300,1031299},29820);
        NisEarnings xiii({238000,262999},{1031300,1139699},33060);
        NisEarnings xiv({263000,291999},{1139700,1265299},36630);
        NisEarnings xv({292000,313799},{1265300,1359999},39990);

        NisEarnings xvi({313800,-1},{136000,-1},41430);

        nisList << i << ii << iii << iv << v << vi << vii << viii << ix << x
                << xi << xii << xiii << xiv << xv << xvi;
    }

    int getNisForSalary(Salary &salary){

        int _salaryAmount = salary.amount();
        SalaryRange range;
        int weeklyContribution = 0;

        foreach (auto i, nisList) {

            auto salaryAmount = _salaryAmount;

            switch (salary.getType()) {

            case Salary::Montly : range = i.getMonthlyRange();
                break;

            case Salary::Weekly : range = i.getWeeklyRange();
                break;

            case Salary::FortNightly : range = i.getWeeklyRange();
                salaryAmount = salaryAmount/2;
                break;
            }

            if(salaryAmount >= range.getMin() &&
                    salaryAmount <= range.getMax()){
                weeklyContribution = i.getTotalWeeklyContribution();
                break;
            }else if(salaryAmount >= range.getMin() && range.getMax() == -1){
                weeklyContribution = i.getTotalWeeklyContribution();
                break;
            }
        }

        switch (salary.getType()) {

        case Salary::Montly : return weeklyContribution*4;
            break;

        case Salary::Weekly : return weeklyContribution;
            break;

        case Salary::FortNightly : return weeklyContribution*2;
            break;
        }

        return 0;
    }

private:
    QList<NisEarnings> nisList;
};

class PayeChecker{
public:
    static int getPayeForSalary(Salary &salary){
        int yearlyProjection = 0;
        int taxCeiling = 7200000;

        switch (salary.getType()) {

        case Salary::Montly : yearlyProjection = salary.amount()*12;
            break;

        case Salary::Weekly : yearlyProjection = salary.amount()*52;
            break;

        case Salary::FortNightly : yearlyProjection = salary.amount()/26;
            break;
        }

        if(yearlyProjection > taxCeiling){
            auto aboveTax = yearlyProjection-taxCeiling;
            auto taxedAmount = aboveTax/4;

            switch (salary.getType()) {

            case Salary::Montly : return taxedAmount/12;
                break;

            case Salary::Weekly : return taxedAmount/52;
                break;

            case Salary::FortNightly : return taxedAmount/26;
                break;
            }
        }

        return 0;
    }
};


class HealthSurchargeCalculator{
public:
    static int getHealthSurcharge(Salary &salary){
        auto amount = salary.amount();
        auto weeklyAmount = 0;
        auto healthSurchargeCeiling = 109;

        switch (salary.getType()) {

        case Salary::Montly : weeklyAmount = amount/4;
            break;

        case Salary::Weekly : weeklyAmount = amount;
            break;

        case Salary::FortNightly : weeklyAmount = amount/2;
            break;
        }

        auto healthSurcharge = 0;

        if(weeklyAmount > healthSurchargeCeiling){
            healthSurcharge = 825;
        }else{
            healthSurcharge = 480;
        }

        switch (salary.getType()) {

        case Salary::Montly : return healthSurcharge*4;
            break;

        case Salary::Weekly : return healthSurcharge;
            break;

        case Salary::FortNightly : return healthSurcharge*2;
            break;
        }

        return 0;
    }
};

void Test::test_salary()
{
    Salary s(Salary::Montly);
    s.setAmount(800000);

    NisChecker checker;
    auto nis = checker.getNisForSalary(s);
    auto paye = PayeChecker::getPayeForSalary(s);
    auto healthSurcharge = HealthSurchargeCalculator::getHealthSurcharge(s);
    auto allTaxes = nis
            + paye
            + healthSurcharge;

    qDebug() << "Gross Pay          : " << s.amount();
    qDebug() << "Net Income         : " << s.amount()-allTaxes;
    qDebug() << "Taxes              : " << allTaxes;
    qDebug() << "NIS                : " << nis;
    qDebug() << "PAYE               : " << paye;
    qDebug() << "Health Surcharge   : " << healthSurcharge;


}

int Salary::amount() const
{
    return _amount;
}

void Salary::setAmount(int amount)
{
    _amount = amount;
}

Salary::SalaryType Salary::getType() const
{
return type;
}

int SalaryRange::getMin() const
{
    return min;
}

int SalaryRange::getMax() const
{
    return max;
}

int NisEarnings::getTotalWeeklyContribution() const
{
    return totalWeeklyContribution;
}

void NisEarnings::setTotalWeeklyContribution(int value)
{
    totalWeeklyContribution = value;
}

SalaryRange NisEarnings::getWeeklyRange() const
{
    return weeklyRange;
}

SalaryRange NisEarnings::getMonthlyRange() const
{
return monthlyRange;
}

QTEST_MAIN(Test)

#include "tst_test.moc"
