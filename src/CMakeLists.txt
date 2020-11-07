cmake_minimum_required(VERSION 3.5)

set(NAME "EnterpriseDomainObjects")

project(${NAME} LANGUAGES CXX)

set(Qt5_DIR "C:\\Felgo\\5.13.2\\msvc2017_64\\lib\\cmake\\Qt5")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED Sql Concurrent Quick Qml)

#qt5_add_resources(RESOURCES resources.qrc)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()

    add_library(${PROJECT_NAME} STATIC
        EnterpriseDomainObjects.h
        Party/AbstractParty.h
        Party/AbstractParty.cpp
        Party/Organization.h
        Party/Organization.cpp
        Party/Party.h
        Party/PartyFacade.h
        Party/PartyFacade.cpp
        Party/Person.h
        Party/Person.cpp
        Party/partymodule.h
        Party/partymodule.cpp
        Party/Salary.h
        Party/Salary.cpp
        Party/SalaryFacade.h
        Party/SalaryFacade.cpp
        Party/Money.h
        Party/Money.cpp
        Party/SalaryDomainObject.h
        Party/SalaryDomainObject.cpp
        Party/DateTime.h
        Party/DateTime.cpp
        Party/CompanyInformationFacade.h
        Party/CompanyInformationFacade.cpp
        Party/OverTimeDomainObject.h
        Party/OverTimeDomainObject.cpp
        Party/Double.h
        Party/Double.cpp
        Party/employeefacade.h
        Party/employeefacade.cpp
        Party/payratedomainobject.h
        Party/payratedomainobject.cpp
        ${PROJECT_NAME}.h
    #        ${RESOURCES}
    )

else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
    add_library(${PROJECT_NAME} STATIC ${PROJECT_NAME}.h)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${CONAN_LIBS} PRIVATE Qt5::Core Qt5::Sql Qt5::Concurrent Qt5::Quick Qt5::Qml)

#target_link_libraries( ${CONAN_LIBS})
#set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
#Replace TEMPLATE_LIBRARY with PROJECTNAME_LIBRARY
target_compile_definitions(${PROJECT_NAME} PRIVATE ENTERPRISEDOMAINOBJECTS_LIBRARY)
