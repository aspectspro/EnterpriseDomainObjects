#include "companyinformationfacade.h"


CompanyInformationFacade::CompanyInformationFacade() {
    loadCompanyInformation();
}

QString CompanyInformationFacade::getId() const
{
    return id;
}

void CompanyInformationFacade::setId(const QString value)
{
    id = value;
    emit idChanged(value);

}

QString CompanyInformationFacade::getAddress() const
{
    return address;
}

void CompanyInformationFacade::setAddress(const QString value)
{
    address = value;
    emit addressChanged(value);
}

QString CompanyInformationFacade::getTelephone_number() const
{
    return telephone_number;
}

void CompanyInformationFacade::setTelephone_number(const QString value)
{
    telephone_number = value;
    emit telephone_numberChanged(value);
}

QString CompanyInformationFacade::getEmail_address() const
{
    return email_address;
}

void CompanyInformationFacade::setEmail_address(const QString value)
{
    email_address = value;
    emit email_addressChanged(value);
}

QString CompanyInformationFacade::getCompany_name() const
{
    return company_name;
}

void CompanyInformationFacade::setCompany_name(const QString value)
{
    company_name = value;
    emit company_nameChanged(value);
}

void CompanyInformationFacade::saveCompanyInformation()
{
    Organization org;
    org.setId("_this_company_");
    org.setCompany_name(getCompany_name());
    org.setAddress(getAddress());
    org.setEmail_address(getEmail_address());
    org.setTelephone_number(getTelephone_number());

    try {
        mapper.insert(org);
    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << "Updating Company Information";
        try {
            mapper.update(org);
        } catch (std::exception &e) {
            Q_UNUSED(e)
            qInfo() << "Error Could not update company Information";
        }
    }
}

void CompanyInformationFacade::loadCompanyInformation()
{

    try {
        auto result = mapper.find(QString("_this_company_"));

        setId(result.getId());
        setCompany_name(result.getCompany_name());
        setAddress(result.getAddress());
        setTelephone_number(result.getTelephone_number());
        setEmail_address(result.getEmail_address());

    } catch (std::exception &e) {
        Q_UNUSED(e)
        qInfo() << "Could not load Company Information";
    }
}
