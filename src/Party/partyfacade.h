#ifndef PARTYFACADE_H
#define PARTYFACADE_H
#include "partymodule.h"
#include "organization.h"

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

#endif // PARTYFACADE_H
