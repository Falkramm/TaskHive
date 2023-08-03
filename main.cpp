//
// Created by daniil on 6/22/23.
//
#include <dao/connectionPool/connectionPool.h>
#include <log4cpp/PropertyConfigurator.hh>
#include <dao/postgres/factory.h>
#include <service/serviceFactory.h>
#include <view/mainscreen.h>
using namespace DAO;
using namespace Service;

int main(int argc, char *argv[])
{    ConnectionPool::getInstance()->init();
    PostgresDAOFactory::init();
    ServiceFactory::init();

    std::shared_ptr<ServiceFactory> factory = std::make_shared<ServiceFactory>();
    std::cout << "Inited\n";
  //  auto tservice = boost::any_cast<std::shared_ptr<TaskService>>(factory->getService(typeid(Task).name()));
//    auto list = tservice->getAll();
//    for(auto user : list)
//        std::cout << *user << '\n';
////    std::cout << *list << "Error\n";
    QApplication a(argc, argv);
   // std::shared_ptr<TaskScreen> screen = std::make_shared<TaskScreen>(tservice->getById("1"));
    std::shared_ptr<MainScreen> screen = std::make_shared<MainScreen>();
    screen->show();
    return a.exec();
}
