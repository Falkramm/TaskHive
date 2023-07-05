//
// Created by daniil on 7/5/23.
//

#ifndef TASKHIVE_SERVICE_H
#define TASKHIVE_SERVICE_H
#include <log4cpp/Category.hh>
#include <boost/any.hpp>
#include <memory>
#include <unordered_map>
#include <utility>
#include <dao/daoFactory.h>
#include <dao/postgres/factory.h>
class ServiceFactory;
class ServiceCreator {
public:
    virtual boost::any create(std::shared_ptr<DAOFactory> pooledConnection) const = 0;//TODO need to recode
};

class Service {
    static log4cpp::Category &logger;

public:
    void setDaoFactory(std::shared_ptr<PostgresDAOFactory> daoFactory) {
        this->daoFactory = daoFactory;
    }

protected:
    std::shared_ptr<PostgresDAOFactory> daoFactory;
    std::shared_ptr<PooledConnection> connection = nullptr;
    boost::any genericDAO;
    std::string entityClass;

protected:
    Service(const std::string &entityClass, std::shared_ptr<PostgresDAOFactory> factory):
    entityClass(entityClass),
    daoFactory(factory)
    {
            connection = daoFactory->getConnection();
            genericDAO = daoFactory->getDao(entityClass);
    }
public:
    virtual std::shared_ptr<Entity> getById(std::string_view id)const = 0;

public:
    virtual std::vector<std::shared_ptr<Entity>> getAll()const = 0;

public:
    virtual std::shared_ptr<Entity> persist(const std::shared_ptr<Entity> object)const = 0;

public:
    virtual void remove(const std::shared_ptr<Entity> object)const = 0;

public:
    virtual void update(const std::shared_ptr<Entity> object)const = 0;

};
log4cpp::Category &Service::logger = log4cpp::Category::getInstance("Service");


class ServiceFactory {
private:
    static log4cpp::Category &logger;
    static std::unordered_map<std::string, std::shared_ptr<ServiceCreator>> creators;
    std::shared_ptr<DAOFactory> factory;
public:
    static void init(){//TODO add services to map
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
    ServiceFactory(std::shared_ptr<DAOFactory> factory):factory(std::move(factory)) {}

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
    void close(){
            factory->close();
    }
};
log4cpp::Category &ServiceFactory::logger = log4cpp::Category::getInstance("ServiceFactory");



#endif //TASKHIVE_SERVICE_H
