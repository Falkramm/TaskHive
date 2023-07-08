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
#include <dao/daoFactory.h>
#include <dao/postgres/factory.h>
#include "service.h"

class ServiceFactory {
private:
    static log4cpp::Category &logger;
    static std::unordered_map<std::string, std::shared_ptr<ServiceCreator>> creators;
    std::shared_ptr<DAOFactory> factory;
public:
    static void init() {//TODO add services to map
//        creators[typeid(User).name(), UserService.class);
//        creators.put(Role.class, RoleService.class);
//        creators.put(Message.class, MessageService.class);
//        creators.put(Chat.class, ChatService.class);
    }

public:
    ServiceFactory() {
        factory = std::make_shared<PostgresDAOFactory>();
    }

public:
    ServiceFactory(std::shared_ptr<DAOFactory> factory) : factory(std::move(factory)) {}

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
};

log4cpp::Category &ServiceFactory::logger = log4cpp::Category::getInstance("ServiceFactory");


#endif //TASKHIVE_SERVICEFACTORY_H
