cmake_minimum_required(VERSION 3.5)

set(NAME "NewTest")

project(${NAME} LANGUAGES CXX)
SET(LIBRARY_NAME_TEST "EnterpriseDomainObjects")

include_directories("../../src")

set(Qt5_DIR "C:\\Felgo\\5.13.2\\msvc2017_64\\lib\\cmake\\Qt5")
set(Qt5Test_DIR "C:\\Felgo\\5.13.2\\msvc2017_64\\lib\\cmake\\Qt5Test")
set(Qt5Gui_DIR "C:\\Felgo\\5.13.2\\msvc2017_64\\lib\\cmake\\Qt5Gui")

find_package(Qt5Test REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED Sql Concurrent PrintSupport)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

find_package(Qt5 COMPONENTS Core REQUIRED Sql Concurrent)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()

    link_directories(${CMAKE_BINARY_DIR}/src/lib)

    add_executable(
        ${PROJECT_NAME}
        tst_newtest.cpp
        employee_v_1.h
        employee_v_1.cpp
        Title/title.h
        Title/TitleInterface.h
        Title/titlemr.cpp
        Title/titlemr.h
        Title/TitlePrefix.h
        Name/name.h
        Name/NameInterface.h
        Name/fullName.h
        Name/fullName.cpp
        Identifier/Identifier.h
        Identifier/IdentifierInterface.h
        Identifier/UuidIdentifier.h
        Title/TitleSuffix.h
        )
    add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARY_NAME_TEST} PRIVATE Qt5::Gui Qt5::Test Qt5::Core Qt5::Sql Qt5::Concurrent Qt5::PrintSupport)

else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()


