#include "titlemr.h"

std::unique_ptr<Title_Interface> TitleMr_ConcreteFactory::create()
{
    return std::make_unique<TitleMr_Concrete>();
}

QString TitleMr_Concrete::name()
{
    return "Mr.";
}
