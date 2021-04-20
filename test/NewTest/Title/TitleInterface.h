#ifndef TITLEINTERFACE_H
#define TITLEINTERFACE_H

#include <QtCore>
#include <memory>

/**
 * @brief The Title_Interface struct
 */
struct Title_Interface{

public:
    virtual QString asString() = 0;

};

typedef std::unique_ptr<Title_Interface> Title;

/**
 * @brief The Title_FactoryInterface struct
 */
struct Title_FactoryInterface{

public:
    virtual Title create() = 0;

};

#endif // TITLEINTERFACE_H
