#include <dao/postgres/postgresTaskDAO.h>

namespace DAO {
    std::string PostgresTaskDAO::getSelectQuery() const {
        return selectQ;
    }

    std::string PostgresTaskDAO::getSelectAllQuery() const {
        return selectALlQ;
    }

    void PostgresTaskDAO::PersistTask::setId(std::string_view id) {
        Task::setId(id);
    }

    std::string PostgresTaskDAO::getCreateQuery() const {
        return insertQ;
    }

    std::string PostgresTaskDAO::getUpdateQuery() const {
        return updateQ;
    }

    std::string PostgresTaskDAO::getDeleteQuery() const {
        return deleteQ;
    }

    std::shared_ptr<Task> PostgresTaskDAO::create() {
        std::shared_ptr<Task> user;
        return AbstractPQXXDao<Task, std::string>::persist(std::move(user));
    }

    std::vector<std::shared_ptr<Task>> PostgresTaskDAO::parseResultSet(const pqxx::result &rs) const {
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

    std::shared_ptr<pqxx::result>
    PostgresTaskDAO::prepareStatementForInsert(pqxx::work &work, std::shared_ptr<Task> object) const {
        auto result = std::make_shared<pqxx::result>(work.exec_params(getCreateQuery(),
                                                                      object->getKey(),
                                                                      object->getTitle(),
                                                                      object->isCompleted(),
                                                                      object->getDescription(),
                                                                      Task::timeToString(object->getStartDate()),
                                                                      Task::timeToString(object->getDeadlineDate())));
        return result;
    }

    std::shared_ptr<pqxx::result>
    PostgresTaskDAO::prepareStatementForUpdate(pqxx::work &work, std::shared_ptr<Task> object) const {
        auto result = std::make_shared<pqxx::result>(work.exec_params(getUpdateQuery(),
                                                                      object->getKey(),
                                                                      object->getTitle(),
                                                                      object->isCompleted(),
                                                                      object->getDescription(),
                                                                      Task::timeToString(object->getStartDate()),
                                                                      Task::timeToString(object->getDeadlineDate()),
                                                                      object->getId()));//TODO maby we need to convert int to string
        return result;
    }

    std::vector<std::shared_ptr<Task>> PostgresTaskDAO::getByUser(const std::shared_ptr<User> user) {
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

    PostgresTaskDAO::PostgresTaskDAO(std::shared_ptr<PooledConnection> connection_)
            : AbstractPQXXDao<Task, std::string>(std::move(connection_)) {}

    std::string PostgresTaskDAO::selectQ = "SELECT * FROM task ";
    std::string PostgresTaskDAO::selectALlQ = "SELECT * FROM task;";
    std::string PostgresTaskDAO::insertQ = "INSERT INTO task (user_id, title, completed, description, startDate, deadlineDate) \nVALUES ($1, $2, $3, $4, $5, $6);";
    std::string PostgresTaskDAO::updateQ = "UPDATE task SET user_id = $1, title = $2, completed = $3, description = $4, startDate = $5, deadlineDate = $6 WHERE id= $7;";
    std::string PostgresTaskDAO::deleteQ = "DELETE FROM task WHERE id= $1;";

    boost::any PostgresTaskDAO::TaskCreator::create(std::shared_ptr<PooledConnection> pooledConnection) const {
        return std::make_shared<PostgresTaskDAO>(pooledConnection);
    }
}