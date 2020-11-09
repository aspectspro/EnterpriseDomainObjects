#include "printerfacade.h"
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>

PrinterFacade::PrinterFacade(QObject *parent) : QObject(parent)
{
    salaryFacade = std::make_unique<SalaryFacade>();
    yearToDateFacade = std::make_unique<SalaryYearToDate>();
    employeeFacade = std::make_unique<EmployeeFacade>();
}

void PrinterFacade::print()
{

}
