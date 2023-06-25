//
// Created by daniil on 6/22/23.
//
#include <dao/connectionPool/connectionPool.h>
#include <log4cpp/PropertyConfigurator.hh>
#include <dao/postgres/factory.h>
int main(){
    ConnectionPool::getInstance()->init();
    PostgresDAOFactory factory;
    auto userDao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(factory.getDao(typeid(User).name()));
    std::cout << "User Dao created\n";
    for(auto &user : userDao->getAll()){
        std::cout << "{User:\t"  << "ID: " << user->getId() << "\tLogin: " << user->getLogin() << "\tPassword: " << user->getPassword() << "}\n";
    }
}