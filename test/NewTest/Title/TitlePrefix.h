#ifndef TITLEPREFIX_H
#define TITLEPREFIX_H
#include "TitleInterface.h"

struct TitlePrefix_Concrete : public Title_Interface{

    // Title_Interface interface
public:
    virtual QString asString() override
    {
        return _data;
    }

    TitlePrefix_Concrete& setTitle(QString title){
        _data = title;
        return *this;
    }

private:
    QString _data;
};

struct TitlePrefix_ConcreteFactory : public Title_FactoryInterface{


    // Title_FactoryInterface interface
public:
    virtual Title create() override
    {
        return std::make_unique<TitlePrefix_Concrete>();
    }
};

struct TitlePrefix_ConcreteBuilder : public TitleBuilder_Interface{

    // TitleBuilder_Interface interface
public:
    TitlePrefix_ConcreteBuilder(){
        initializeFactory();
        reset();
    }

    virtual TitleBuilder_Interface &initializeFactory() override
    {
        this->_titleFactory = std::make_unique<TitlePrefix_ConcreteFactory>();
        return *this;
    }

    TitlePrefix_ConcreteBuilder &from(Title_Interface &title){
        _cast()->setTitle(title.asString());
        return *this;
    }

    TitlePrefix_ConcreteBuilder& mr(){
        _cast()->setTitle("Mr");
        return *this;
    }

    TitlePrefix_ConcreteBuilder& ms(){
        _cast()->setTitle("Ms");
        return *this;
    }

    TitlePrefix_ConcreteBuilder& mrs(){
        _cast()->setTitle("Mrs");
        return *this;
    }

    TitlePrefix_ConcreteBuilder& dr(){
        _cast()->setTitle("Dr");
        return *this;
    }

private:
    TitlePrefix_Concrete* _cast(){
        return dynamic_cast<TitlePrefix_Concrete*>(_title.get());
    }

};




#endif // TITLEPREFIX_H
