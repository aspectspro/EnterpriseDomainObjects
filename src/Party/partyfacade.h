#ifndef PARTYFACADE_H
#define PARTYFACADE_H
#include "partymodule.h"
#include "organization.h"
#include "person.h"

/**
 * @brief The EnterpriseDateUtils class - Utilities for Date Formatting.
 */
class EnterpriseDateUtils : public QObject{
    Q_OBJECT

public slots:
    static DateTime now();

    static DateTime dateTimeFromTimestamp(int timestamp);

    static DateTime dateTimeFromUtc(QString utcTime);

    static QString appDatesView(int timestamp);

    static QString appDatesView(QDateTime dateTime);
};

class PartyFacade : public QObject
{
    Q_OBJECT

signals:
    void error(QString message);

public:
    PartyFacade();

public slots:
    QAbstractItemModel *organizationModel();
    Organization createOrganization(QString company_name, QString email_address, QString address, QString telephone_number);    
    void save(Organization organization);
    void load();

protected:
    void insert(Organization organization);

private:
    DomainModelPtr _organizationModel;

};

//class EmployeeFacade : public QObject{

//    Q_OBJECT
//    Q_PROPERTY(QAbstractItemModel* employeeModel READ getEmployeeModel)

//signals:
//    void error(QString message);

//public:
//    EmployeeFacade();

//public slots:
//    static Employee employeeFactory();
//    void saveEmployee(Employee employee);
//    void removeEmployee(Employee employee);
//    void updateEmployee(Employee employee);
//    Employee find(QString id = "");

//    QAbstractItemModel *getEmployeeModel();

//    void loadEmployees();

//private:
//    EmployeeMapper mapper;
//    DomainModelPtr employeeModel;
//};



#endif // PARTYFACADE_H
