//
// Created by daniil on 6/25/23.
//

#ifndef TASKHIVE_POSTGRESUSERDAO_H
#define TASKHIVE_POSTGRESUSERDAO_H

#include <dao/abstractPQXXDao.h>
#include <utility>
#include <entity/User.h>

class PostgresUserDAO : public AbstractPQXXDao<User, std::string> {
private:
    static std::string selectQ;
    static std::string selectALlQ;
    static std::string insertQ;
    static std::string updateQ;
    static std::string deleteQ;

    class PersistTask : public User {
    public:
        void setId(std::string_view id) override {
            User::setId(id);
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

    std::unique_ptr<User> create() override {
        std::unique_ptr<User> user;
        return AbstractPQXXDao<User, std::string>::persist(std::move(user));
    }

    std::vector<std::unique_ptr<User>> parseResultSet(const pqxx::result &rs) const override {
        std::vector<std::unique_ptr<User>> result;
        try {
            for (pqxx::row v: rs) {
                PostgresUserDAO::PersistTask user;
                user.setId(v.at("id").as<std::string>());
                user.setLogin(v.at("username").as<std::string>());
                user.setPassword(v.at("password_hash").as<std::string>());
                result.emplace_back(std::make_unique<User>(user));
            }
        } catch (std::exception e) {
            throw PersistException(e);
        }
        return result;
    }

    void prepareStatementForInsert(pqxx::prepare::invocation &invocation, std::unique_ptr<User> object) const override {
        try {
            invocation(object->getLogin());
            invocation(object->getPassword());
        } catch (std::exception e) {
            throw PersistException(e);
        }
    }

    void prepareStatementForUpdate(pqxx::prepare::invocation &invocation, std::unique_ptr<User> object) const override {
        try {
            invocation(object->getLogin());
            invocation(object->getPassword());
            invocation(object->getId());
        } catch (std::exception e) {
            throw PersistException(e);
        }
    }

    std::unique_ptr<User> getByLogin(const std::string &login) {
        try {
            std::vector<std::unique_ptr<User>> list;
            const std::string sql = getSelectQuery() + " WHERE login = $1";
            pqxx::work txn(*connection);
            pqxx::result rs = txn.exec_params(sql, login);
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

public:
    PostgresUserDAO(std::shared_ptr<DAOFactory> parentFactory, std::shared_ptr<PooledConnection> connection)
            : AbstractPQXXDao<User, std::string>(std::move(parentFactory), std::move(connection)) {}
};

std::string PostgresUserDAO::selectQ = "SELECT * FROM user";
std::string PostgresUserDAO::selectALlQ = "SELECT * FROM user";
std::string PostgresUserDAO::insertQ = "INSERT INTO user (login, password) \nVALUES ($1, $2);";
std::string PostgresUserDAO::updateQ = "UPDATE user SET login=$1, password=$2 WHERE id= $3;";
std::string PostgresUserDAO::deleteQ = "DELETE FROM user WHERE id=$1;";

#endif //TASKHIVE_POSTGRESUSERDAO_H
