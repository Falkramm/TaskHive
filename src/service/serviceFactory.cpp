#include <service/serviceFactory.h>

namespace Service {
    void ServiceFactory::init() {//TODO add services to map
        creators.insert({typeid(User).name(), std::make_shared<UserServiceCreator>()});
        creators.insert({typeid(Task).name(), std::make_shared<TaskServiceCreator>()});
    }

    ServiceFactory::ServiceFactory(std::shared_ptr<PostgresDAOFactory> factory) : factory(std::move(factory)) {}

    ServiceFactory::ServiceFactory() : ServiceFactory(std::make_shared<PostgresDAOFactory>()) {}

    boost::any ServiceFactory::getService(const std::string &objectName) {
        std::shared_ptr<ServiceCreator> creator = nullptr;
        if (creators.contains(objectName)) {
            creator = creators.find(objectName)->second;
        } else {
            throw PersistException("Service object for " + objectName + " not found.");
        }
        return creator->create(factory);
    }

    void ServiceFactory::close() {
        factory->close();
    }

    ServiceFactory::~ServiceFactory() {
        close();
    }

    std::unordered_map<std::string, std::shared_ptr<ServiceCreator>> ServiceFactory::creators;
    log4cpp::Category &ServiceFactory::logger = log4cpp::Category::getInstance("ServiceFactory");
}
