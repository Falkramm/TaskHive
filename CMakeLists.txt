cmake_minimum_required(VERSION 3.25)
project(TaskHive)
# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
enable_testing()
include_directories(${CMAKE_SOURCE_DIR}/include)
#           GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#           Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#           PQXX
link_directories(/usr/lib/x86_64-linux-gnu/)
include_directories(/usr/lib/x86_64-linux-gnu)
# Add executable and source files
add_executable(TaskHive
        main.cpp
        include/entity/Entity.h
        include/entity/serializable.h
        include/entity/identified.h
        include/entity/User.h
        src/entity/Entity.cpp
        include/entity/Task.h
        src/entity/User.cpp
        src/entity/Task.cpp
        include/dao/connectionPool/connectionPool.h
        include/dao/genericDao.h
        include/dao/daoFactory.h
        include/dao/abstractPQXXDao.h
        include/dao/persistException.h
        include/dao/postgres/postgresUserDAO.h
        include/dao/postgres/postgresTaskDAO.h
        include/dao/postgres/factory.h)
target_link_libraries(TaskHive PRIVATE pqxx)
target_link_libraries(TaskHive PRIVATE -llog4cpp)
target_link_libraries(TaskHive PRIVATE Boost::boost)

#               DAO Testing
add_executable(MyTest
        test/dao/PostgresUserDaoTests.cpp
        include/entity/Entity.h
        include/entity/serializable.h
        include/entity/identified.h
        include/entity/User.h
        src/entity/Entity.cpp
        include/entity/Task.h
        src/entity/User.cpp
        src/entity/Task.cpp
        include/dao/connectionPool/connectionPool.h
        include/dao/genericDao.h
        include/dao/daoFactory.h
        include/dao/abstractPQXXDao.h
        include/dao/persistException.h
        include/dao/postgres/postgresUserDAO.h
        include/dao/postgres/postgresTaskDAO.h
        include/dao/postgres/factory.h include/service/service.h include/service/userService.h include/service/serviceFactory.h include/service/taskService.h)
target_link_libraries(MyTest PRIVATE ${GTEST_LIBRARIES})
target_link_libraries(MyTest PRIVATE pthread)
target_link_libraries(MyTest PRIVATE pqxx)
target_link_libraries(MyTest PRIVATE -llog4cpp)
target_link_libraries(MyTest PRIVATE Boost::boost)
