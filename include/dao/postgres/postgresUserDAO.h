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

    std::shared_ptr<User> create() override {
        std::shared_ptr<User> user;
        return AbstractPQXXDao<User, std::string>::persist(std::move(user));
    }

    std::vector<std::shared_ptr<User>> parseResultSet(const pqxx::result &rs) const override {
        std::vector<std::shared_ptr<User>> result;
        try {
            std::cout << "Result size: " << rs.size() << '\n';
            for (pqxx::row v: rs) {
                PostgresUserDAO::PersistTask user;
                user.setId(v.at("id").as<std::string>());
                user.setLogin(v.at("login").as<std::string>());
                user.setPassword(v.at("password").as<std::string>());
                result.emplace_back(std::make_shared<User>(user));
            }
        } catch (std::exception e) {
            throw PersistException(e);
        }
        return result;
    }

    void prepareStatementForInsert(pqxx::prepare::invocation &invocation, std::shared_ptr<User> object) const override {
        try {
            invocation(object->getLogin());
            invocation(object->getPassword());
        } catch (std::exception e) {
            throw PersistException(e);
        }
    }

    void prepareStatementForUpdate(pqxx::prepare::invocation &invocation, std::shared_ptr<User> object) const override {
        try {
            invocation(object->getLogin());
            invocation(object->getPassword());
            invocation(object->getId());
        } catch (std::exception e) {
            throw PersistException(e);
        }
    }

    std::shared_ptr<User> getByLogin(const std::string &login) {
        try {
            std::vector<std::shared_ptr<User>> list;
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
    PostgresUserDAO(std::shared_ptr<PooledConnection> connection)
            : AbstractPQXXDao<User, std::string>(std::move(connection)) {}
};

std::string PostgresUserDAO::selectQ = "SELECT * FROM customers";
std::string PostgresUserDAO::selectALlQ = "SELECT * FROM customers";
std::string PostgresUserDAO::insertQ = "INSERT INTO customers (login, password) \nVALUES ($1, $2);";
std::string PostgresUserDAO::updateQ = "UPDATE customers SET login=$1, password=$2 WHERE id= $3;";
std::string PostgresUserDAO::deleteQ = "DELETE FROM customers WHERE id=$1;";

#endif //TASKHIVE_POSTGRESUSERDAO_H