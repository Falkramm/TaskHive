# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(TaskHive)

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
    include/controller/Action/action.h
    include/controller/Action/actionManager.h
    include/controller/dispatcher/dispatcher.h
    include/controller/Filter/actionFromUriFilter.h
    include/controller/Filter/encodingFilter.h
    include/controller/Filter/filter.h
    include/controller/Filter/filterFactory.h
    include/controller/Filter/securityFilter.h
    include/controller/Prepairing/prepare.h
    include/controller/controller.h
    include/dao/DAO
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
    include/entity/serializable.h
    include/entity/Task.h
    include/entity/User.h
    include/service/service.h
    include/service/serviceFactory.h
    include/service/taskService.h
    include/service/userService.h
    src/entity/Entity.cpp
    src/entity/Task.cpp
    src/entity/User.cpp
    test/dao/PostgresUserDaoTests.cpp
    CMakeLists.txt
    main.cpp
    README.md
)




add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE pqxx)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE -llog4cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Boost::boost)
