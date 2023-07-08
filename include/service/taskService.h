//
// Created by daniil on 7/8/23.
//

#ifndef TASKHIVE_TASKSERVICE_H
#define TASKHIVE_TASKSERVICE_H
#include "service.h"

class TaskService: public Service<Task>{
public:
    TaskService(const std::shared_ptr<PostgresDAOFactory> &factory) : Service(typeid(Task).name(), factory) {}

    std::shared_ptr<Task> getById(const std::string &id) const override {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(daoFactory);
        return dao->getByPrimaryKey(id);
    }

    std::vector<std::shared_ptr<Task>> getAll() const override {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(daoFactory);
        return dao->getAll();
    }

    std::shared_ptr<Task> persist(const std::shared_ptr<Task> object) const override {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(daoFactory);
        return dao->persist(object);
    }

    void remove(const std::shared_ptr<Task> object) const override {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(daoFactory);
        dao->remove(object);
    }

    void update(const std::shared_ptr<Task> object) const override {
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(daoFactory);
        dao->update(object);
    }
    std::vector<std::shared_ptr<Task>> getByUser(const std::shared_ptr<User> user){
        auto dao = boost::any_cast<std::shared_ptr<PostgresTaskDAO>>(daoFactory);
        return dao->getByUser(user);
    }
};
class TaskServiceCreator: public ServiceCreator{
public:
    boost::any create(std::shared_ptr<PostgresDAOFactory> daoFactory) const override {
        return std::make_shared<TaskService>(daoFactory);
    }
};

#endif //TASKHIVE_TASKSERVICE_H
