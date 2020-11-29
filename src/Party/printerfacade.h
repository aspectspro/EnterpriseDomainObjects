#ifndef PRINTERFACADE_H
#define PRINTERFACADE_H

#include <QtCore>
#include <QPrinter>
#include <QtPrintSupport>
#include "salaryfacade.h"
#include "employeefacade.h"
#include "paytypedomainobject.h"
#include "companyinformationfacade.h"

class PrinterFacade : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString salary_id READ getSalary_id WRITE setSalary_id NOTIFY salary_idChanged)

public:
    explicit PrinterFacade(QObject *parent = nullptr);    

    QString getSalary_id() const;
    void setSalary_id(const QString &value);

public slots:
    void print();

signals:
    void salary_idChanged(QString salary_id);
    void finishedPrint();

private:
    std::unique_ptr<QPrintDialog> printer;

    std::unique_ptr<SalaryDomainObject> salaryFacade;
    std::unique_ptr<SalaryYearToDate> yearToDateFacade;
    std::unique_ptr<EmployeeFacade> employeeFacade;
    std::unique_ptr<PaytypeFacade> paytypeFacade;
    std::unique_ptr<CompanyInformationFacade> companyFacade;
    QString salary_id;
    QTextDocument doc;
    static SalaryDomainMapper salaryMapper;

private slots:
    void _sendToPrint(int result);

};

#endif // PRINTERFACADE_H
