//
// Created by daniil on 6/22/23.
//
#include <dao/connectionPool/connectionPool.h>
#include <log4cpp/PropertyConfigurator.hh>
#include <dao/postgres/factory.h>

int main(){
    ConnectionPool::getInstance()->init();
    PostgresDAOFactory factory;
    auto taskDao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(factory.getDao(typeid(Task).name()));
    std::shared_ptr<Task> task = std::make_shared<Task>();
    task->setTitle("Hellooooooooo");
    task->setKey("1");
    std::cout << *task << '\n';
    auto result= taskDao->getByPrimaryKey("1");
    result->setCompleted(true);
    taskDao->update(result);
    result = taskDao->getByPrimaryKey("1");
    std::cout << *result;
}