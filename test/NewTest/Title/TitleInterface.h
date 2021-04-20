#ifndef TITLEINTERFACE_H
#define TITLEINTERFACE_H

#include <QtCore>
#include <memory>

/**
 * @brief The Title_Interface struct
 */
struct Title_Interface{

public:
    virtual QString name() = 0;

};

/**
 * @brief The Title_FactoryInterface struct
 */
struct Title_FactoryInterface{

public:
    virtual std::unique_ptr<Title_Interface> create() = 0;

};

#endif // TITLEINTERFACE_H
