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

//    boost::posix_time::ptime pTimeFromString(std::string str)const {
//        boost::posix_time::ptime datetime = boost::posix_time::time_from_string(str);
//        boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
//        boost::posix_time::time_duration duration = datetime - epoch;
//        auto start_time = std::chrono::high_resolution_clock::now();
//
//        // Execute a SELECT query to read data from a table
//        pqxx:: my_timestamp = result_set.at(0).at("mytimestamp").as<pqxx::timestamp>();
//
//        // End the timer and calculate the elapsed time in milliseconds
//        auto end_time = std::chrono::high_resolution_clock::now();
//        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
//
//        return datetime;
//    }
    std::vector<std::shared_ptr<Task>> parseResultSet(const pqxx::result &rs) const override {
        std::vector<std::shared_ptr<Task>> result;
        for (pqxx::row v: rs) {
            PostgresTaskDAO::PersistTask task;
            task.setId(v.at("id").as<std::string>());
            task.setKey(v.at("user_id").as<std::string>());
            task.setTitle(v.at("title").as<std::string>());
            task.setCompleted(v.at("completed").as<bool>());
            task.setDescription(v.at("description").as<std::string>());
            task.setStartDate(std::chrono::system_clock::now());
            task.setDeadlineDate(
                    std::chrono::system_clock::now());//TODO make normal converter from timestamp to c++ types
//            task.setStartDate(
//                    std::chrono::system_clock::time_point(
//                            std::chrono::seconds (std::stoll(v.at("startdate").as<std::string>()))
//                    )
//            );
//            task.setDeadlineDate(std::chrono::system_clock::time_point(
//                    std::chrono::seconds(std::stoll(v.at("deadlinedate").as<std::string>()))
//            ));
            result.emplace_back(std::make_shared<Task>(task));
        }
        return result;
    }

protected:
    std::string timeToString(const std::chrono::system_clock::time_point &point) const {
        auto time_t = std::chrono::system_clock::to_time_t(point);
        std::stringstream ss;
        ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    std::shared_ptr<pqxx::result>
    prepareStatementForInsert(pqxx::work &work, std::shared_ptr<Task> object) const override {
        auto result = std::make_shared<pqxx::result>(work.exec_params(getCreateQuery(),
                                                                      object->getKey(),
                                                                      object->getTitle(),
                                                                      object->isCompleted(),
                                                                      object->getDescription(),
                                                                      timeToString(object->getStartDate()),
                                                                      timeToString(object->getStartDate())));
        return result;
    }

    std::shared_ptr<pqxx::result>
    prepareStatementForUpdate(pqxx::work &work, std::shared_ptr<Task> object) const override {
        auto result = std::make_shared<pqxx::result>(work.exec_params(getUpdateQuery(),
                                                                      object->getKey(),
                                                                      object->getTitle(),
                                                                      object->isCompleted(),
                                                                      object->getDescription(),
                                                                      timeToString(object->getStartDate()),
                                                                      timeToString(object->getDeadlineDate()),
                                                                      object->getId()));//TODO maby we need to convert int to string
        return result;
    }

public:
    std::vector<std::shared_ptr<Task>> getByUser(const std::shared_ptr<User> user) {
        try {
            std::vector<std::shared_ptr<Task>> list;
            //TODO convert login to hash key;
            pqxx::work txn(*connection);
            pqxx::result rs = txn.exec_params(getSelectQuery() + " WHERE user_id = $1;", user->getId());
            list = parseResultSet(rs);
            txn.commit();
            return list;
        } catch (const std::exception &e) {
            throw PersistException(e.what());
        }
    }

public:
    [[maybe_unused]] PostgresTaskDAO(std::shared_ptr<PooledConnection> connection_)
            : AbstractPQXXDao<Task, std::string>(std::move(connection_)) {}
};

std::string PostgresTaskDAO::selectQ = "SELECT * FROM task ";
std::string PostgresTaskDAO::selectALlQ = "SELECT * FROM task;";
std::string PostgresTaskDAO::insertQ = "INSERT INTO task (user_id, title, completed, description, startDate, deadlineDate) \nVALUES ($1, $2, $3, $4, $5, $6);";
std::string PostgresTaskDAO::updateQ = "UPDATE task SET user_id = $1, title = $2, completed = $3, description = $4, startDate = $5, deadlineDate = $6 WHERE id= $7;";
std::string PostgresTaskDAO::deleteQ = "DELETE FROM task WHERE id= $1;";
#endif //TASKHIVE_POSTGRESTASKDAO_H
