//
// Created by daniil on 6/22/23.
//
#include <connectionPool.h>
#include <log4cpp/PropertyConfigurator.hh>
#include <factory.h>
#include <serviceFactory.h>
int main(){
    ConnectionPool::getInstance()->init();
    PostgresDAOFactory::init();
    ServiceFactory::init();

    std::shared_ptr<ServiceFactory> factory = std::make_shared<ServiceFactory>();
    std::cout << "Inited\n";
    auto tservice = boost::any_cast<std::shared_ptr<TaskService>>(factory->getService(typeid(Task).name()));
    auto uservice = boost::any_cast<std::shared_ptr<UserService>>(factory->getService(typeid(User).name()));
    auto user = uservice->getById("10");
    std::cout << *user;
    auto list = tservice->getByUser(user);
    for(auto user : list)
        std::cout << *user << '\n';
}
