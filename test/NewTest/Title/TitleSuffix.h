#ifndef TITLESUFFIX_H
#define TITLESUFFIX_H

#include "TitlePrefix.h"

struct TitleSuffix_Concrete : public TitlePrefix_Concrete{

};

struct TitleSuffix_ConcreteFactory : public Title_FactoryInterface{


    // Title_FactoryInterface interface
public:
    virtual Title create() override
    {
        return std::make_unique<TitleSuffix_Concrete>();
    }
};

struct TitleSuffix_ConcreteBuilder : public TitleBuilder_Interface{


    // TitleBuilder_Interface interface
public:
    TitleSuffix_ConcreteBuilder(){
        initializeFactory();
        reset();
    }

    virtual TitleBuilder_Interface &initializeFactory() override
    {
        this->_titleFactory = std::make_unique<TitleSuffix_ConcreteFactory>();
        return *this;
    }

    TitleSuffix_ConcreteBuilder& jr(){
        _cast()->setTitle("Jr");
        return *this;
    }

    TitleSuffix_ConcreteBuilder& sr(){
        _cast()->setTitle("Sr");
        return *this;
    }

private:
    TitleSuffix_Concrete* _cast(){
        return dynamic_cast<TitleSuffix_Concrete*>(_title.get());
    }

};


#endif // TITLESUFFIX_H
