//
// Created by daniil on 6/22/23.
//
#include <dao/connectionPool/connectionPool.h>
#include <log4cpp/PropertyConfigurator.hh>
#include <dao/postgres/factory.h>
#include <service/serviceFactory.h>
#include <view/screen/tasklistscreen.h>
using namespace DAO;
using namespace Service;
//int main(){
//    ConnectionPool::getInstance()->init();
//    PostgresDAOFactory::init();
//    ServiceFactory::init();

//    std::shared_ptr<ServiceFactory> factory = std::make_shared<ServiceFactory>();
//    std::cout << "Inited\n";
//    auto tservice = boost::any_cast<std::shared_ptr<TaskService>>(factory->getService(typeid(Task).name()));
//    auto uservice = boost::any_cast<std::shared_ptr<UserService>>(factory->getService(typeid(User).name()));
//    auto user = uservice->getById("10");
//    std::cout << *user;
//    auto list = tservice->getByUser(user);
//    for(auto user : list)
//        std::cout << *user << '\n';
//}


int main(int argc, char *argv[])
{    ConnectionPool::getInstance()->init();
    PostgresDAOFactory::init();
    ServiceFactory::init();

    std::shared_ptr<ServiceFactory> factory = std::make_shared<ServiceFactory>();
    std::cout << "Inited\n";
    auto tservice = boost::any_cast<std::shared_ptr<TaskService>>(factory->getService(typeid(Task).name()));
    auto list = tservice->getAll();
    for(auto user : list)
        std::cout << *user << '\n';
//    std::cout << *list << "Error\n";
    QApplication a(argc, argv);
    std::shared_ptr<TaskListScreen> screen = std::make_shared<TaskListScreen>(list);
    screen->show();
    return a.exec();
}
