cmake_minimum_required(VERSION 3.25)
project(TaskHive)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(/usr/lib/x86_64-linux-gnu/)
include_directories(/usr/lib/x86_64-linux-gnu)
add_executable(TaskHive main.cpp include/entity/Entity.h include/entity/User.h src/entity/Entity.cpp include/entity/Task.h src/entity/User.cpp src/entity/Task.cpp include/dao/connectionPool/connectionPool.h main.cpp include/dao/genericDao.h include/entity/identified.h include/entity/serializable.h include/dao/daoFactory.h include/dao/abstractPQXXDao.h include/dao/persistException.h)
target_link_libraries(TaskHive PRIVATE pqxx)
target_link_libraries(TaskHive PRIVATE -llog4cpp)