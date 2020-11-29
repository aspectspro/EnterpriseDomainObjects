#include "partyfacade.h"

PartyFacade::PartyFacade()
{
    _organizationModel = ModelFactory::createModel<Organization>();
    Core core;
    core.initializeCoreTables();

    PartyModule partyModule;
    partyModule.install();

    DomainObjectListPtr data = std::make_shared<QList<DomainObjectPtr>>();
    _organizationModel->changeDomainList(data);

}

QAbstractItemModel *PartyFacade::organizationModel()
{
    return _organizationModel.get();
}

Organization PartyFacade::createOrganization(QString company_name, QString email_address, QString address, QString telephone_number)
{
    Organization org;
    org.setCompany_name(company_name);
    org.setAddress(address);
    org.setTelephone_number(telephone_number);
    org.setEmail_address(email_address);
    org.generateId();
    return org;

}

void PartyFacade::insert(Organization organization)
{
    _organizationModel->insert(organization.clone());
}

void PartyFacade::save(Organization organization)
{
    OrganizationMapper mapper;
    try {
        mapper.insert(organization);
        insert(organization);
    } catch (std::exception &e) {
        emit error(e.what());
    }
}

void PartyFacade::load()
{
    OrganizationMapper mapper;
    auto all = mapper.loadAll();

    DomainObjectListPtr data = std::make_shared<QList<DomainObjectPtr>>();
    data->clear();

    foreach (auto i, all) {
        data->append(i.clone());
    }
    _organizationModel->changeDomainList(data);

}

DateTime EnterpriseDateUtils::now(){
    return DateTime::getNow();
}

DateTime EnterpriseDateUtils::dateTimeFromTimestamp(qint64 timestamp){
    DateTime dt;
    dt.setTimestamp(timestamp);
    return dt;
}

DateTime EnterpriseDateUtils::dateTimeFromUtc(QString utcTime){
    auto secs = QDateTime::fromString(utcTime).toSecsSinceEpoch()+43200;
    DateTime dt;
    dt.setTimestamp(secs);
    return dt;
}

QString EnterpriseDateUtils::appDatesView(qint64 timestamp){
    auto dt = QDateTime::fromSecsSinceEpoch(timestamp+43200);
    return dt.toString("yyyy-MM-dd");
}

QString EnterpriseDateUtils::appDatesView(QDateTime dateTime){
    return appDatesView(dateTime.toSecsSinceEpoch());
}
