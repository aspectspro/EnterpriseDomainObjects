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
    qint64 mondayChecker();

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
        Montly,
        None
    };

    Salary();
    Salary(SalaryDateRange salaryDates);

    qint64 amount() const;
    void setAmount(qint64 amount);

    SalaryType getType() const;
    SalaryDateRange getSalaryDates() const;

private:
    qint64 _amount = 0;
    SalaryType type = None;
    SalaryDateRange salaryDates;
};

/**
 * @brief The SalaryRange class - Holder of salary ranges.
 */
class SalaryRange{

public:
    SalaryRange(){}
    SalaryRange(qint64 min,qint64 max);
    qint64 getMin() const;

    qint64 getMax() const;

private:
    qint64 min;
    qint64 max;
};

/**
 * @brief The NisEarnings class - Holder of NIS tax information.
 */
class NisEarnings{

public:
    NisEarnings(SalaryRange weeklyRange, SalaryRange monthlyRange, qint64 totalWeeklyContribution);

    qint64 getAssumedWeekly() const;
    void setAssumedWeekly(qint64 value);

    qint64 getEmployerWeekly();
    qint64 getEmployeeWeekly();

    qint64 getTotalWeeklyContribution() const;
    void setTotalWeeklyContribution(qint64 value);

    SalaryRange getWeeklyRange() const;
    SalaryRange getMonthlyRange() const;

private:
    SalaryRange weeklyRange;
    SalaryRange monthlyRange;
    qint64 totalWeeklyContribution = 0;
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
    static qint64 getNisForSalary(Salary &salary);

    /**
     * @brief getNisForSalary
     * @return
     */
    qint64 getNisForSalary();

    /**
     * @brief getEmployeeContribution
     * @return
     */
    qint64 getEmployeeContribution();

    /**
     * @brief getEmployerContribution
     * @return
     */
    qint64 getEmployerContribution();

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
    static qint64 getPayeForSalary(Salary &salary);
};

/**
 * @brief The HealthSurchargeCalculator class - Calculates Health surcharge. 4.80 if
 * salary < 10900 per week or 825 if salary >= 10900
 *
 */
class HealthSurchargeCalculator{
public:
    static qint64 getHealthSurcharge(Salary &salary);
};



#endif // SALARY_H
