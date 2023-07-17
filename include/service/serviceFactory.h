//
// Created by daniil on 7/8/23.
//

#ifndef TASKHIVE_SERVICEFACTORY_H
#define TASKHIVE_SERVICEFACTORY_H

#include <log4cpp/Category.hh>
#include <boost/any.hpp>
#include <memory>
#include <unordered_map>
#include <utility>
#include <service/service.h>
#include <service/userService.h>
#include <service/taskService.h>
namespace Service{
    class ServiceFactory {
    private:
        static log4cpp::Category &logger;
        static std::unordered_map<std::string, std::shared_ptr<ServiceCreator>> creators;
        std::shared_ptr<PostgresDAOFactory> factory;
    public:
        static void init() {//TODO add services to map
            creators.insert({typeid(User).name(), std::make_shared<UserServiceCreator>()});
            creators.insert({typeid(Task).name(), std::make_shared<TaskServiceCreator>()});
        }



    public:
        ServiceFactory(std::shared_ptr<PostgresDAOFactory> factory) : factory(std::move(factory)) {}
    public:
        ServiceFactory(): ServiceFactory(std::make_shared<PostgresDAOFactory>()){}
    public:
        virtual boost::any getService(const std::string &objectName) {
            std::shared_ptr<ServiceCreator> creator = nullptr;
            if (creators.contains(objectName)) {
                creator = creators.find(objectName)->second;
            } else {
                throw PersistException("Service object for " + objectName + " not found.");
            }
            return creator->create(factory);
        }

    public:
        void close() {
            factory->close();
        }

        virtual ~ServiceFactory(){
            close();
        }
    };
    std::unordered_map<std::string, std::shared_ptr<ServiceCreator>> ServiceFactory::creators;
    log4cpp::Category &ServiceFactory::logger = log4cpp::Category::getInstance("ServiceFactory");

}

#endif //TASKHIVE_SERVICEFACTORY_H
