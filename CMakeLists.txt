# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(TaskHive)
#           AddQt
list(APPEND CMAKE_PREFIX_PATH "/home/daniil/Qt/6.5.1/gcc_64")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
#           GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#           Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#           PQXX
link_directories(/usr/lib/x86_64-linux-gnu/)
include_directories(/usr/lib/x86_64-linux-gnu)

include_directories(
    include
)

set (SRCS
    configuration/log4cpp.xml
    databases/sql/create.sql
    databases/sql/drop.sql
    databases/sql/generate.sql
    databases/sql/trunc.sql
    include/controller/dispatcher/dispatcher.h
    include/controller/controller.h
    include/dao/DAO.h
    include/dao/connectionPool/connectionPool.h
    include/dao/postgres/factory.h
    include/dao/postgres/postgresTaskDAO.h
    include/dao/postgres/postgresUserDAO.h
    include/dao/abstractPQXXDao.h
    include/dao/daoFactory.h
    include/dao/genericDao.h
    include/dao/persistException.h
    include/entity/Entity.h
    include/entity/identified.h
        include/entity/Task.h
    include/entity/User.h
    include/service/service.h
    include/service/serviceFactory.h
    include/service/taskService.h
    include/service/userService.h
    include/view/view.h
    include/view/mainscreen.h

    include/view/screen/screen.h
    include/view/screen/taskscreen.h
    include/view/screen/tasklistscreen.h
    include/view/screen/loginscreen.h
        src/entity/Entity.cpp
    src/entity/Task.cpp
    src/entity/User.cpp
    src/view/mainscreen.cpp
    src/view/screen/loginscreen.cpp
    CMakeLists.txt
    main.cpp
    README.md src/dao/connectionPool/connectionPool.cpp src/dao/persistException.cpp src/dao/postgres/postgresUserDAO.cpp src/dao/postgres/postgresTaskDAO.cpp src/dao/postgres/factory.cpp src/service/serviceFactory.cpp src/service/userService.cpp src/service/taskService.cpp src/controller/dispatcher/dispatcher.cpp
        src/view/screen/tasklistscreen.cpp
        src/view/screen/taskscreen.cpp)


set(RESOURCE_FILES resourses.qrc)
qt6_add_resources(RESOURCE_SOURCES ${RESOURCE_FILES})

add_executable(${CMAKE_PROJECT_NAME} ${SRCS} ${RESOURCE_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE pqxx)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE -llog4cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Boost::boost)
