#include "salary.h"

QList<NisEarnings> NisCalculator::nisList;

SalaryDateRange::SalaryDateRange()
{

}

SalaryDateRange::SalaryDateRange(QString from, QString to){
    fromDate = convertFromString(from);
    toDate = convertFromString(to);
}

qint64 SalaryDateRange::mondayChecker(){

    auto daysDifference = fromDate.daysTo(toDate);
    qint64 mondayCounter = 0;

    for(qint64 i = 0; i <= daysDifference; i++){
        QDate _dtFrom = fromDate.addDays(i);
        if(_dtFrom.dayOfWeek() == 1){
            mondayCounter = mondayCounter+1;
        }
    }

    auto wks = mondayCounter == 0 ? 1 : mondayCounter;    

    return wks;
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
    }else if(mondayCounter == 4){
        type = Montly;
    }else if(mondayCounter == 5 && salaryDates.getToDate().month() == salaryDates.getFromDate().month()){
        type = Montly;
    }
    else{
        type = None;
    }
}

SalaryRange::SalaryRange(qint64 min, qint64 max){
    this->min = min;
    this->max = max;
}

NisEarnings::NisEarnings(SalaryRange weeklyRange, SalaryRange monthlyRange, qint64 totalWeeklyContribution) :
    weeklyRange(weeklyRange),monthlyRange(monthlyRange), totalWeeklyContribution(totalWeeklyContribution){}

qint64 NisEarnings::getEmployerWeekly(){
    return getTotalWeeklyContribution()/1.5;
}

qint64 NisEarnings::getEmployeeWeekly(){
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

qint64 NisCalculator::getNisForSalary(Salary &salary){

    NisCalculator();

    qint64 _salaryAmount = salary.amount();
    SalaryRange range;
    qint64 weeklyContribution = 0;
    auto weeks = salary.getSalaryDates().mondayChecker();

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

        case Salary::None : range = i.getWeeklyRange();
            salaryAmount = (salaryAmount/weeks);
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

    return weeklyContribution*weeks;
}

qint64 NisCalculator::getNisForSalary()
{
    return getNisForSalary(this->salary);
}

qint64 NisCalculator::getEmployeeContribution()
{
    return getNisForSalary()/3;
}

qint64 NisCalculator::getEmployerContribution()
{
    return getNisForSalary()/1.5;
}

qint64 PayeCalculator::getPayeForSalary(Salary &salary){
    qint64 yearlyProjection = 0;
    qint64 taxCeiling = 7200000;

    auto weeks = salary.getSalaryDates().mondayChecker();    

    switch (salary.getType()) {

    case Salary::FortNightly : yearlyProjection = (salary.amount()/2)*52;
        break;

    case Salary::None : yearlyProjection = (salary.amount()/weeks)*52;
        break;

    case Salary::Weekly : yearlyProjection = (salary.amount())*52;
        break;

    case Salary::Montly : yearlyProjection = salary.amount()*12;
        break;        

    }    

    if(yearlyProjection > taxCeiling){

        auto aboveTax = yearlyProjection-taxCeiling;
        auto taxedAmount = aboveTax/4;

        qDebug() << weeks << "PAYE weeks" << yearlyProjection << (taxedAmount/52)*weeks;

        switch (salary.getType()) {

        default: return (taxedAmount/52)*weeks;

        case Salary::Montly : return taxedAmount/12;
            break;
        }
    }

    return 0;
}

qint64 HealthSurchargeCalculator::getHealthSurcharge(Salary &salary){
    auto amount = salary.amount();
    auto weeklyAmount = 0;
    auto healthSurchargeCeiling = 10900;

    auto weeks = salary.getSalaryDates().mondayChecker();

    switch (salary.getType()) {

    case Salary::Montly : weeklyAmount = amount/4;
        break;

    case Salary::Weekly : weeklyAmount = amount;
        break;

    case Salary::FortNightly : weeklyAmount = amount/2;
        break;

    case Salary::None : weeklyAmount = amount/weeks;
        break;
    }

    auto healthSurcharge = 0;

    if(weeklyAmount > healthSurchargeCeiling){
        healthSurcharge = 825;
    }else{
        healthSurcharge = 480;
    }

    return healthSurcharge*weeks;
}

qint64 Salary::amount() const
{
    return _amount;
}

void Salary::setAmount(qint64 amount)
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

qint64 SalaryRange::getMin() const
{
    return min;
}

qint64 SalaryRange::getMax() const
{
    return max;
}

qint64 NisEarnings::getTotalWeeklyContribution() const
{
    return totalWeeklyContribution;
}

void NisEarnings::setTotalWeeklyContribution(qint64 value)
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
