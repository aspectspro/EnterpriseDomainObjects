#ifndef TITLEINTERFACE_H
#define TITLEINTERFACE_H

#include "../src/EnterpriseDomainObjects.h"

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

typedef std::unique_ptr<Title_FactoryInterface> TitleFactory;

struct TitleBuilder_Interface{

public:
    /**
     * @brief reset - Resets builder Title interface.
     * @return
     */
    virtual TitleBuilder_Interface& reset(){
        this->_title = _titleFactory->create();
        return *this;
    };

    /**
     * @brief build - Builds product as unique_ptr, remember to call std::move(unique_ptr);
     * @return
     */
    virtual Title build(){
        auto _temp = std::move(_title);
        reset();
        return _temp;
    };

    /**
      @brief initializeFactory - Initializes Factory; Call from constructor of subclass.
     */

    virtual TitleBuilder_Interface& initializeFactory() = 0;

protected:
    Title _title;
    TitleFactory _titleFactory;

};


#endif // TITLEINTERFACE_H
