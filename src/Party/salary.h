#ifndef SALARY_H
#define SALARY_H
#include <QtCore>

/**
 * @brief The SalaryDateRange class - Range of dates for salary.
 */
class SalaryDateRange{

public:
    SalaryDateRange();
    SalaryDateRange(QString from, QString to);

    /**
     * @brief getWeekDifference - Returns the difference of week number.
     * @return
     */
    int mondayChecker();

    /**
     * @brief convertFromString - Converts from dateString yyyy-MM-dd
     * @param dateString
     * @return
     */
    static QDate convertFromString(QString dateString);

    QDate getFromDate() const;
    QDate getToDate() const;

    void setFromDate(const QString value);
    void setToDate(const QString value);

private:
    QDate fromDate;
    QDate toDate;
};

/**
 * @brief The Salary class - Holds basic information about salary. Requires date range.
 */
class Salary{

public:
    enum SalaryType{
        Weekly,
        FortNightly,
        Montly
    };

    Salary();
    Salary(SalaryDateRange salaryDates);

    int amount() const;
    void setAmount(int amount);

    SalaryType getType() const;
    SalaryDateRange getSalaryDates() const;

private:
    int _amount = 0;
    SalaryType type;
    SalaryDateRange salaryDates;
};

/**
 * @brief The SalaryRange class - Holder of salary ranges.
 */
class SalaryRange{

public:
    SalaryRange(){}
    SalaryRange(int min,int max);
    int getMin() const;

    int getMax() const;

private:
    int min;
    int max;
};

/**
 * @brief The NisEarnings class - Holder of NIS tax information.
 */
class NisEarnings{

public:
    NisEarnings(SalaryRange weeklyRange, SalaryRange monthlyRange, int totalWeeklyContribution);

    int getAssumedWeekly() const;
    void setAssumedWeekly(int value);

    int getEmployerWeekly();
    int getEmployeeWeekly();

    int getTotalWeeklyContribution() const;
    void setTotalWeeklyContribution(int value);

    SalaryRange getWeeklyRange() const;
    SalaryRange getMonthlyRange() const;

private:
    SalaryRange weeklyRange;
    SalaryRange monthlyRange;
    int totalWeeklyContribution = 0;
};


/**
 * @brief The NisChecker class - Calculates NIS from salary.
 */
class NisCalculator{

public:
    NisCalculator();
    NisCalculator(Salary salary) : salary(salary){}

    /**
     * @brief getNisForSalary
     * @return
     */
    static int getNisForSalary(Salary &salary);

    /**
     * @brief getNisForSalary
     * @return
     */
    int getNisForSalary();

    /**
     * @brief getEmployeeContribution
     * @return
     */
    int getEmployeeContribution();

    /**
     * @brief getEmployerContribution
     * @return
     */
    int getEmployerContribution();

private:
    static QList<NisEarnings> nisList;
    Salary salary;
};

/**
 * @brief The PayeChecker class - Calculates PAYE from salary.
 * Projects the yearly salary and then returns 25% salary date range.
 */
class PayeCalculator{
public:
    static int getPayeForSalary(Salary &salary);
};

/**
 * @brief The HealthSurchargeCalculator class - Calculates Health surcharge. 4.80 if
 * salary < 10900 per week or 825 if salary >= 10900
 *
 */
class HealthSurchargeCalculator{
public:
    static int getHealthSurcharge(Salary &salary);
};



#endif // SALARY_H
