#include "salary.h"

QList<NisEarnings> NisCalculator::nisList;

SalaryDateRange::SalaryDateRange()
{

}

SalaryDateRange::SalaryDateRange(QString from, QString to){
    fromDate = convertFromString(from);
    toDate = convertFromString(to);
}

int SalaryDateRange::mondayChecker(){

    auto fromDayOfMonth = fromDate.dayOfYear();
    auto toDayOfMonth = toDate.dayOfYear();
    auto daysDifference = toDayOfMonth-fromDayOfMonth;
    int mondayCounter = 0;

    for(int i = 0; i <= daysDifference; i++){
        QDate _dtFrom = fromDate.addDays(i);
        if(_dtFrom.dayOfWeek() == 1){
            mondayCounter++;
        }
    }

    return mondayCounter;
}

QDate SalaryDateRange::convertFromString(QString dateString){
    return QDate::fromString(dateString,Qt::ISODate);
}

Salary::Salary()
{

}

Salary::Salary(SalaryDateRange salaryDates) :
    salaryDates(salaryDates){
    auto mondayCounter = salaryDates.mondayChecker();

    if(mondayCounter == 1 || mondayCounter == 0){
        type = Weekly;
    }else if(mondayCounter == 2){
        type = FortNightly;
    }else if(mondayCounter >= 3){
        type = Montly;
    }
}

SalaryRange::SalaryRange(int min, int max){
    this->min = min;
    this->max = max;
}

NisEarnings::NisEarnings(SalaryRange weeklyRange, SalaryRange monthlyRange, int totalWeeklyContribution) :
    weeklyRange(weeklyRange),monthlyRange(monthlyRange), totalWeeklyContribution(totalWeeklyContribution){}

int NisEarnings::getEmployerWeekly(){
    return getTotalWeeklyContribution()/1.5;
}

int NisEarnings::getEmployeeWeekly(){
    return getTotalWeeklyContribution()/3;
}

NisCalculator::NisCalculator(){

    //Checks if nisList is initialized.
    if(nisList.count() > 1)
        return;

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

int NisCalculator::getNisForSalary(Salary &salary){

    NisCalculator();

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

    return weeklyContribution*salary.getSalaryDates().mondayChecker();
}

int NisCalculator::getNisForSalary()
{
    return getNisForSalary(this->salary);
}

int NisCalculator::getEmployeeContribution()
{
    return getNisForSalary()/3;
}

int NisCalculator::getEmployerContribution()
{
    return getNisForSalary()/1.5;
}

int PayeCalculator::getPayeForSalary(Salary &salary){
    int yearlyProjection = 0;
    int taxCeiling = 8400000;

    switch (salary.getType()) {

    case Salary::Montly : yearlyProjection = salary.amount()*12;
        break;

    case Salary::Weekly : yearlyProjection = salary.amount()*52;
        break;

    case Salary::FortNightly : yearlyProjection = salary.amount()*26;
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

int HealthSurchargeCalculator::getHealthSurcharge(Salary &salary){
    auto amount = salary.amount();
    auto weeklyAmount = 0;
    auto healthSurchargeCeiling = 10900;

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

    return healthSurcharge*salary.getSalaryDates().mondayChecker();
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

SalaryDateRange Salary::getSalaryDates() const
{
    return salaryDates;
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



QDate SalaryDateRange::getFromDate() const
{
    return fromDate;
}

QDate SalaryDateRange::getToDate() const
{
    return toDate;
}

void SalaryDateRange::setFromDate(const QString value)
{
    fromDate = convertFromString(value);
}

void SalaryDateRange::setToDate(const QString value)
{
    toDate = convertFromString(value);
}
