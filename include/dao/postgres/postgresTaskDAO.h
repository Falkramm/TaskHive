//
// Created by daniil on 6/25/23.
//

#ifndef TASKHIVE_POSTGRESTASKDAO_H
#define TASKHIVE_POSTGRESTASKDAO_H


#include <dao/abstractPQXXDao.h>
#include <utility>
#include <entity/Task.h>//TODO
#include "entity/User.h"

class PostgresTaskDAO : public AbstractPQXXDao<Task, std::string> {
private:
    static std::string selectQ;
    static std::string selectALlQ;
    static std::string insertQ;
    static std::string updateQ;
    static std::string deleteQ;

    class PersistTask : public Task {
    public:
        void setId(std::string_view id) override {
            Task::setId(id);
        }
    };

    std::string getSelectQuery() const override {
        return selectQ;
    }

    std::string getSelectAllQuery() const override {
        return selectALlQ;
    }

    std::string getCreateQuery() const override {
        return insertQ;
    }

    std::string getUpdateQuery() const override {
        return updateQ;
    }

    std::string getDeleteQuery() const override {
        return deleteQ;
    }

    std::shared_ptr<Task> create() override {
        std::shared_ptr<Task> user;
        return AbstractPQXXDao<Task, std::string>::persist(std::move(user));
    }
public:
    [[maybe_unused]] PostgresTaskDAO(std::shared_ptr<PooledConnection> connection)
            : AbstractPQXXDao<Task, std::string>(std::move(connection)) {}

    std::vector<std::shared_ptr<Task>> parseResultSet(const pqxx::result &rs) const override {
        std::vector<std::shared_ptr<Task>> result;
        try {
            for (pqxx::row v: rs) {
                PostgresTaskDAO::PersistTask task;
                task.setId(v.at("id").as<std::string>());
                task.setKey(v.at("key").as<std::string>());
                task.setTitle(v.at("title").as<std::string>());
                task.setCompleted(v.at("completed").as<bool>());
                task.setDescription(v.at("description").as<std::string>());
                task.setStartDate(std::chrono::system_clock::from_time_t(v.at("startdate").as<int>()));
                task.setDeadlineDate(std::chrono::system_clock::from_time_t(v.at("deadline").as<int>()));
                result.emplace_back(std::make_shared<Task>(task));
            }
        } catch (std::exception e) {
            throw PersistException(e);
        }
        return result;
    }
protected:
    void prepareStatementForInsert(pqxx::prepare::invocation &invocation, std::shared_ptr<Task> object) const override {
        try {
            invocation(object->getKey());
            invocation(object->getTitle());
            invocation(object->isCompleted());
            invocation(object->getDescription());
            invocation(std::chrono::system_clock::to_time_t(object->getStartDate()));
            invocation(std::chrono::system_clock::to_time_t(object->getDeadlineDate()));
        } catch (std::exception e) {
            throw PersistException(e);
        }
    }

    void prepareStatementForUpdate(pqxx::prepare::invocation &invocation, std::shared_ptr<Task> object) const override {
        try {
            invocation(object->getKey());
            invocation(object->getTitle());
            invocation(object->isCompleted());
            invocation(object->getDescription());
            invocation(std::chrono::system_clock::to_time_t(object->getStartDate()));
            invocation(std::chrono::system_clock::to_time_t(object->getDeadlineDate()));
            invocation(object->getId());//TODO maby we need to convert int to string
        } catch (std::exception e) {
            throw PersistException(e);
        }
    }
public:
    std::shared_ptr<Task> getByUser(const std::shared_ptr<User> user) {
        try {
            std::vector<std::shared_ptr<Task>> list;
            const std::string sql = getSelectQuery() + " WHERE key = $1";//TODO convert login to hash key;
            pqxx::work txn(*connection);
            pqxx::result rs = txn.exec_params(sql, user->getLogin());
            list = parseResultSet(rs);
            if (list.empty()) {
                return nullptr;
            }
            if (list.size() > 1) {
                throw PersistException("Received more than one record.");
            }
            return std::move(list.front());
        } catch (const std::exception &e) {
            throw PersistException(e.what());
        }
    }
};

std::string PostgresTaskDAO::selectQ = "SELECT * FROM task";
std::string PostgresTaskDAO::selectALlQ = "SELECT * FROM task";
std::string PostgresTaskDAO::insertQ = "INSERT INTO task (key, title, completed, description, startdate, deadline) \nVALUES ($1, $2, $3, $4, $5, $6);";
std::string PostgresTaskDAO::updateQ = "UPDATE task SET key = $1, title = $2, completed = $3, description = $4, startdate = $5, deadline = $6) WHERE id= $7;";
std::string PostgresTaskDAO::deleteQ = "DELETE FROM task WHERE id= $1;";
#endif //TASKHIVE_POSTGRESTASKDAO_H
