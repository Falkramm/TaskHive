//
// Created by daniil on 6/22/23.
//
#include <dao/connectionPool/connectionPool.h>
#include <log4cpp/PropertyConfigurator.hh>
#include <dao/postgres/factory.h>
#include <service/serviceFactory.h>
int main(){
    ConnectionPool::getInstance()->init();
    PostgresDAOFactory::init();
    ServiceFactory::init();

    std::shared_ptr<ServiceFactory> factory = std::make_shared<ServiceFactory>();
    std::cout << "Inited\n";
    auto service = boost::any_cast<std::shared_ptr<UserService>>(factory->getService(typeid(User).name()));
    auto list = service->getAll();
    for(auto user : list)
        std::cout << *user << '\n';
}