#include "printerfacade.h"
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QtGui>
SalaryDomainMapper PrinterFacade::salaryMapper;

PrinterFacade::PrinterFacade(QObject *parent) : QObject(parent)
{
    salaryFacade = std::make_unique<SalaryDomainObject>();
    yearToDateFacade = std::make_unique<SalaryYearToDate>();
    employeeFacade = std::make_unique<EmployeeFacade>();
    paytypeFacade = std::make_unique<PaytypeFacade>();
    companyFacade = std::make_unique<CompanyInformationFacade>();
    printer = std::make_unique<QPrintDialog>();

    connect(this,&PrinterFacade::salary_idChanged,[=](QString salary_id){
        auto s = salaryMapper.find(salary_id);
        salaryFacade.release();
        salaryFacade = std::make_unique<SalaryDomainObject>(s);
        yearToDateFacade->setSalary_id(salaryFacade->getId());
        employeeFacade->setId(salaryFacade->getEmployee_id());
        paytypeFacade->setId(salaryFacade->getEmployee_id());
    });

    connect(printer.get(),SIGNAL(finished(int)),this,SLOT(_sendToPrint(int)));
}

void PrinterFacade::print()
{
    auto firstName = employeeFacade->getFirst_name();
    auto lastName = employeeFacade->getLast_name();
    auto nisNumber = employeeFacade->getNis_number();
    auto birNumber = employeeFacade->getBir_number();
    auto employmentTitle = paytypeFacade->getEmployee_title();

    auto datePaid =  salaryFacade->getDate_paid().toIsoDate();
    auto dateFrom = salaryFacade->getDate_from().toIsoDate();
    auto dateTo = salaryFacade->getDate_to().toIsoDate();

    auto gross = salaryFacade->getGross_pay();
    auto net = salaryFacade->getNet_pay();
    auto nis = salaryFacade->getEmployee_nis();
    auto paye = salaryFacade->getPaye();
    auto hsc = salaryFacade->getHealth_surcharge();

    auto ytdGross = yearToDateFacade->getYearGross();
    auto ytdNet = yearToDateFacade->getYearNet();
    auto ytdNis = yearToDateFacade->getYearNis();
    auto ytdPaye = yearToDateFacade->getYearPaye();
    auto ytdHsc = yearToDateFacade->getYearHealthSurcharge();

    auto companyName = companyFacade->getCompany_name();
    auto companyAddress = companyFacade->getAddress();
    auto companyPhone = companyFacade->getTelephone_number();
    auto companyEmail = companyFacade->getEmail_address();

    QStringList companyDetails;

    companyDetails << "<h2>Company Name   : "+companyName;
    companyDetails << "Address        : "+companyAddress;
    companyDetails <<   "Phone        : "+companyPhone;
    companyDetails <<   "Email        : "+companyEmail+"</h2>";

    auto _details = companyDetails.join("<br>").prepend("<div class='company'>").append("</div>").append("<br><hr>");

    QStringList heading;

    heading << "<h3>Payslip Date    : "+datePaid ;
    heading << "Employee Name       : "+firstName+" "+lastName;
    heading << "Employee Title      : "+employmentTitle;
    heading << "NIS #      : "+nisNumber;
    heading << "BIR #      : "+birNumber;
    heading << "Pay Period : "+dateFrom+" to "+dateTo+"</h3>";

    auto header = heading.join("<br>").append("<hr>").prepend("<div>").append("</div>");

    doc.setDefaultStyleSheet("th,td {padding: 15px; text-align: left;}, .companyDetails{ font-size : 30px }");

    QStringList summary;

    summary << "<table>";

    summary << "<tr>";
    summary << "<th><h4>Gross Pay</th>";
    summary << "<th>NIS</th>";
    summary << "<th>PAYE</th>";
    summary << "<th>Health Surcharge</th>";
    summary << "<th>NET Pay</h4></th>";

    summary << "<tr><h5>";
    summary << "<td> "+gross.asString()+"</td>";
    summary << "<td>"+nis.asString()+"</td>";
    summary << "<td>"+paye.asString()+"</td>";
    summary << "<td>"+hsc.asString()+"</td>";
    summary << "<td>"+net.asString()+"</td>";
    summary << "</h5></tr>";

    summary << "<tr>";
    summary << "<th colspan='5'><hr></th>";
    summary << "</tr>";

    summary << "<tr>";
    summary << "<th><h4>YTD Gross Pay</th>";
    summary << "<th>YTD NIS</th>";
    summary << "<th>YTD PAYE</th>";
    summary << "<th>YTD Health Surcharge</th>";
    summary << "<th>YTD NET Pay</h4></th>";
    summary << "</tr>";

    summary << "<tr><h5>";
    summary << "<td> "+ytdGross.asString()+"</td>";
    summary << "<td>"+ytdNis.asString()+"</td>";
    summary << "<td>"+ytdPaye.asString()+"</td>";
    summary << "<td>"+ytdHsc.asString()+"</td>";
    summary << "<td>"+ytdNet.asString()+"</td>";
    summary << "</h5></tr>";

    summary << "</table><br><hr>";

    auto summaryHtml = summary.join("");

    doc.setHtml("<body>"+_details+header.append(summaryHtml)+"</body>");

    //Open Print Dialog
    printer->exec();
}

QString PrinterFacade::getSalary_id() const
{
    return salary_id;
}

void PrinterFacade::setSalary_id(const QString &value)
{
    salary_id = value;
    emit salary_idChanged(value);
}

void PrinterFacade::_sendToPrint(int result)
{
    if(result == QDialog::Accepted){
        doc.print(printer->printer());
    }

    emit finishedPrint();
}
