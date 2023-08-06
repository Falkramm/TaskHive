#include <service/taskService.h>

namespace Service {

    TaskService::TaskService(const std::shared_ptr<PostgresDAOFactory> &factory) : Service(typeid(Task).name(),
                                                                                           factory) {}

    std::shared_ptr<Task> TaskService::getById(const std::string &id) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(genericDAO);
        return dao->getByPrimaryKey(id);
    }

    std::vector<std::shared_ptr<Task>> TaskService::getAll() const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(genericDAO);
        return dao->getAll();
    }

    std::shared_ptr<Task> TaskService::persist(const std::shared_ptr<Task> object) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(genericDAO);
        return dao->persist(object);
    }

    void TaskService::remove(const std::shared_ptr<Task> object) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(genericDAO);
        dao->remove(object);
    }

    void TaskService::update(const std::shared_ptr<Task> object) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(genericDAO);
        dao->update(object);
    }

    std::vector<std::shared_ptr<Task>> TaskService::getByUser(const std::shared_ptr<User> user) {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(genericDAO);
        return dao->getByUser(user);
    }

    boost::any TaskServiceCreator::create(std::shared_ptr<PostgresDAOFactory> daoFactory) const {
        return std::make_shared<TaskService>(daoFactory);
    }
}