//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_ABSTRACTPQXXDAO_H
#define TASKHIVE_ABSTRACTPQXXDAO_H


#include <pqxx/pqxx>
#include <vector>
#include "genericDao.h"
#include "entity/identified.h"
#include "connectionPool/connectionPool.h"
#include "persistException.h"

template<typename T, typename PK>
requires std::is_same_v<T, Identified<PK>>
class AbstractPQXXDao : public GenericDAO<T, PK>, public std::enable_shared_from_this<AbstractPQXXDao<T, PK>> {
public:
    AbstractPQXXDao(std::shared_ptr<PooledConnection> connection_) : connection(std::move(connection_)) {}

    virtual ~AbstractPQXXDao() {}

    virtual std::unique_ptr<T> getByPrimaryKey(PK key) override {
        std::vector<std::unique_ptr<T>> list;
        std::string sql = getSelectQuery() + " WHERE id = $1";
        pqxx::prepare::invocation invoc(getPQXXConnection(), sql);
        invoc(std::to_string(key));
        pqxx::result result = invoc.exec();

        for (const auto& row : result) {
            list.push_back(parseRow(row));
        }

        if (list.empty()) {
            return nullptr;
        }
        if (list.size() > 1) {
            throw PersistException("Received more than one record.");
        }
        return std::move(list[0]);
    }

    virtual std::vector<std::unique_ptr<T>> getAll() override {
        std::vector<std::unique_ptr<T>> list;
        std::string sql = getSelectAllQuery();
        pqxx::prepare::invocation invoc(getPQXXConnection(), sql);
        pqxx::result result = invoc.exec();

        for (const auto& row : result) {
            list.push_back(parseRow(row));
        }

        return list;
    }

    virtual std::unique_ptr<T> persist(T object) override {
        if (!object.getId().empty()) {
            throw PersistException("Object is already persisted.");
        }

        std::unique_ptr<T> persistInstance;
        // Добавляем запись
        std::string sql = getCreateQuery();
        pqxx::prepare::invocation invoc(getPQXXConnection(), sql);
        bindInsertParams(invoc, object);
        pqxx::result result = invoc.exec();

        if (result.affected_rows() != 1) {
            throw PersistException("On persist modify more than 1 record: " + std::to_string(result.affected_rows()));
        }

        // Получаем только что вставленную запись
        sql = getSelectQuery() + " WHERE id = lastval()";
        pqxx::result result2 = getPQXXConnection().exec(sql);
        for (const auto& row : result2) {
            persistInstance = parseRow(row);
        }

        return persistInstance;
    }

    virtual void update(T object) override {
        std::string sql = getUpdateQuery();
        pqxx::prepare::invocation invoc(getPQXXConnection(), sql);
        bindUpdateParams(invoc, object);
        pqxx::result result = invoc.exec();
        if (result.affected_rows() != 1) {
            throw PersistException("On update modify more than 1 record: " + std::to_string(result.affected_rows()));
        }
    }

    virtual void deleteObject(T object) override {
        std::string sql = getDeleteQuery();
        pqxx::prepare::invocation invoc(getPQXXConnection(), sql);
        invoc(object.getId());
        pqxx::result result = invoc.exec();
        if (result.affected_rows() != 1) {
            throw PersistException("On delete modify more than 1 record: " + std::to_string(result.affected_rows()));
        }
    }

protected:
    std::shared_ptr<PooledConnection> connection;

    pqxx::connection& getPQXXConnection() {
        return *(connection->get_base_connection());
    }

    virtual std::string getSelectQuery() = 0;
    virtual std::string getSelectAllQuery() = 0;
    virtual std::string getCreateQuery() = 0;
    virtual std::string getUpdateQuery() = 0;
    virtual std::string getDeleteQuery() = 0;

    virtual std::unique_ptr<T> parseRow(const pqxx::row& row) = 0;
    virtual void bindInsertParams(pqxx::prepare::invocation& invoc, const T& object) =0;
    virtual void bindUpdateParams(pqxx::prepare::invocation& invoc, const T& object) = 0;
};


#endif //TASKHIVE_ABSTRACTPQXXDAO_H
