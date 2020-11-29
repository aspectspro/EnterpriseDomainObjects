#ifndef EMPLOYEEFACADE_H
#define EMPLOYEEFACADE_H
#include "person.h"

class EmployeeFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QAbstractItemModel* employeeModel READ getEmployeeModel)

    Q_PROPERTY(QString _id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString first_name READ getFirst_name WRITE setFirst_name NOTIFY first_nameChanged)
    Q_PROPERTY(QString last_name READ getLast_name WRITE setLast_name NOTIFY last_nameChanged)
    Q_PROPERTY(QString telephone_number READ getTelephone_number WRITE setTelephone_number NOTIFY telephone_numberChanged)
    Q_PROPERTY(QString address READ getAddress WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString email_address READ getEmail_address WRITE setEmail_address NOTIFY email_addressChanged)
    Q_PROPERTY(QString identification_number READ getIdentification_number WRITE setIdentification_number NOTIFY identification_numberChanged)
    Q_PROPERTY(QString driver_permit_number READ getDriver_permit_number WRITE setDriver_permit_number NOTIFY driver_permit_numberChanged)
    Q_PROPERTY(QString passport_number READ getPassport_number WRITE setPassport_number NOTIFY passport_numberChanged)
    Q_PROPERTY(DateTime date_of_birth READ getDate_of_birth WRITE setDate_of_birth NOTIFY date_of_birthChanged)
    Q_PROPERTY(QString bir_number READ getBir_number WRITE setBir_number NOTIFY bir_numberChanged)
    Q_PROPERTY(QString nis_number READ getNis_number WRITE setNis_number NOTIFY nis_numberChanged)
    Q_PROPERTY(DateTime date_of_employment READ getDate_of_employment WRITE setDate_of_employment NOTIFY date_of_employmentChanged)
    Q_PROPERTY(DateTime date_of_discharge READ getDate_of_discharge WRITE setDate_of_discharge NOTIFY date_of_dischargeChanged)


public:
    explicit EmployeeFacade(QObject *parent = nullptr);

    QString getId() const;
    void setId(const QString &value);

    QString getFirst_name() const;
    void setFirst_name(const QString &value);

    QString getLast_name() const;
    void setLast_name(const QString &value);

    QString getTelephone_number() const;
    void setTelephone_number(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

    QString getEmail_address() const;
    void setEmail_address(const QString &value);

    QString getIdentification_number() const;
    void setIdentification_number(const QString &value);

    QString getDriver_permit_number() const;
    void setDriver_permit_number(const QString &value);

    QString getPassport_number() const;
    void setPassport_number(const QString &value);

    DateTime getDate_of_birth() const;
    void setDate_of_birth(const DateTime &value);

    QString getBir_number() const;
    void setBir_number(const QString &value);

    QString getNis_number() const;
    void setNis_number(const QString &value);

    DateTime getDate_of_employment() const;
    void setDate_of_employment(const DateTime &value);

    DateTime getDate_of_discharge() const;
    void setDate_of_discharge(const DateTime &value);

signals:
    void idChanged(QString id);
    void first_nameChanged(QString first_name);
    void last_nameChanged(QString last_name);
    void telephone_numberChanged(QString telephone_number);
    void addressChanged(QString address);
    void email_addressChanged(QString email_address);
    void identification_numberChanged(QString identification_number);
    void driver_permit_numberChanged(QString driver_permit_number);
    void passport_numberChanged(QString passport_number);
    void date_of_birthChanged(DateTime date_of_birth);
    void bir_numberChanged(QString bir_number);
    void nis_numberChanged(QString nis_number);
    void date_of_employmentChanged(DateTime date_of_employment);
    void date_of_dischargeChanged(DateTime date_of_discharge);

    void employeeSavedChanged(Employee employee);

private:
    QString id,first_name,last_name,telephone_number,address,email_address;
    QString identification_number, driver_permit_number,passport_number;
    DateTime date_of_birth;
    QString bir_number,nis_number;
    DateTime date_of_employment,date_of_discharge;


public slots:
    void save();
    void load();

    static QAbstractItemModel *getEmployeeModel();
    static void loadEmployees();
private:

    static EmployeeMapper mapper;
    static DomainModelPtr employeeModel;

};

#endif // EMPLOYEEFACADE_H
