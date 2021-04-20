#ifndef TITLEMR_H
#define TITLEMR_H
#include "TitleInterface.h"

/**
 * @brief The TitleMr_Concrete struct
 */
struct TitleMr_Concrete : public Title_Interface{

    // Title_Interface interface
public:
    virtual QString name() override;
};

/**
 * @brief The TitleMr_ConcreteFactory struct
 */
struct TitleMr_ConcreteFactory : public Title_FactoryInterface{
    // Title_FactoryInterface interface
public:
    virtual std::unique_ptr<Title_Interface> create() override;
};

/**
 * @brief The TitleMrs_Concrete struct
 */
struct TitleMrs_Concrete : public Title_Interface{

    // Title_Interface interface
public:
    virtual QString name() override
    {
        return "Mrs.";
    }
};

/**
 * @brief The TitleMrs_ConcreteFactory struct
 */
struct TitleMrs_ConcreteFactory : public Title_FactoryInterface{
    // Title_FactoryInterface interface
public:
    virtual std::unique_ptr<Title_Interface> create() override
    {
        return std::make_unique<TitleMrs_Concrete>();
    }
};

/**
 * @brief The TitleMs_Concrete struct
 */
struct TitleMs_Concrete : public Title_Interface{

    // Title_Interface interface
public:
    virtual QString name() override
    {
        return "Ms";
    }
};

/**
 * @brief The TitleMs_ConcreteFactory struct
 */
struct TitleMs_ConcreteFactory : public Title_FactoryInterface{
    // Title_FactoryInterface interface
public:
    virtual std::unique_ptr<Title_Interface> create() override
    {
        return std::make_unique<TitleMs_Concrete>();
    }
};

/**
 * @brief The TitleDr_Concrete struct
 */
struct TitleDr_Concrete : public Title_Interface{


    // Title_Interface interface
public:
    virtual QString name() override
    {
        return "Dr";
    }
};

/**
 * @brief The TitleDr_ConcreteFactory struct
 */
struct TitleDr_ConcreteFactory : public Title_FactoryInterface{
    // Title_FactoryInterface interface
public:
    virtual std::unique_ptr<Title_Interface> create() override
    {
        return std::make_unique<TitleDr_Concrete>();
    }
};



#endif // TITLEMR_H
