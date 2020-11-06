#ifndef COMPANYINFORMATIONFACADE_H
#define COMPANYINFORMATIONFACADE_H
#include <QtCore>
#include "organization.h"

class CompanyInformationFacade : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString company_name READ getCompany_name WRITE setCompany_name NOTIFY company_nameChanged)
    Q_PROPERTY(QString address READ getAddress WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString telephone_number READ getTelephone_number WRITE setTelephone_number NOTIFY telephone_numberChanged)
    Q_PROPERTY(QString email_address READ getEmail_address WRITE setEmail_address NOTIFY email_addressChanged)

signals:
    void idChanged(QString id);
    void company_nameChanged(QString company_name);
    void addressChanged(QString address);
    void email_addressChanged(QString email_address);
    void telephone_numberChanged(QString telephone_number);

public:
    CompanyInformationFacade();
    virtual ~CompanyInformationFacade() {}

    QString getId() const;
    void setId(const QString value);

    QString getAddress() const;
    void setAddress(const QString value);

    QString getTelephone_number() const;
    void setTelephone_number(const QString value);

    QString getEmail_address() const;
    void setEmail_address(const QString value);

    QString getCompany_name() const;
    void setCompany_name(const QString value);

public slots:
    void saveCompanyInformation();
    void loadCompanyInformation();


private:
    QString id, address, telephone_number, email_address, company_name;
    OrganizationMapper mapper;
};



#endif // COMPANYINFORMATIONFACADE_H
