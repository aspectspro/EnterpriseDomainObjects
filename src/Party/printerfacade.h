#ifndef PRINTERFACADE_H
#define PRINTERFACADE_H

#include <QtCore>
#include <QPrinter>
#include <QtPrintSupport>
#include "salaryfacade.h"
#include "employeefacade.h"

class PrinterFacade : public QObject
{
    Q_OBJECT
public:
    explicit PrinterFacade(QObject *parent = nullptr);
    void print();

signals:

private:
    std::unique_ptr<QPrintDialog> printer;

    std::unique_ptr<SalaryFacade> salaryFacade;
    std::unique_ptr<SalaryYearToDate> yearToDateFacade;
    std::unique_ptr<EmployeeFacade> employeeFacade;

};

#endif // PRINTERFACADE_H
