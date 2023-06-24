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
#include "daoFactory.h"

template<typename T, typename PK> requires DerivedFromIdentified<T, PK>
class AbstractPQXXDao : public GenericDAO<T, PK>, public std::enable_shared_from_this<AbstractPQXXDao<T, PK>> {
public:
    /**
     * Возвращает sql запрос для получения одной записи.
     * <p/>
     * SELECT * FROM [Table]
     */
    virtual std::string_view getSelectQuery() const = 0;

    /**
     * Возвращает sql запрос для получения всех записей.
     * <p/>
     * SELECT * FROM [Table]
     */
    virtual std::string_view getSelectAllQuery() const = 0;

    /**
     * Возвращает sql запрос для вставки новой записи в базу данных.
     * <p/>
     * INSERT INTO [Table] ([column, column, ...]) VALUES (?, ?, ...);
     */
    virtual std::string_view getCreateQuery() const = 0;

    /**
     * Возвращает sql запрос для обновления записи.
     * <p/>
     * UPDATE [Table] SET [column = ?, column = ?, ...] WHERE id = ?;
     */
    virtual std::string_view getUpdateQuery() const = 0;

    /**
     * Возвращает sql запрос для удаления записи из базы данных.
     * <p/>
     * DELETE FROM [Table] WHERE id= ?;
     */
    virtual std::string_view getDeleteQuery() const = 0;

    /**
     * Разбирает ResultSet и возвращает список объектов соответствующих содержимому ResultSet.
     */
protected:

    virtual std::vector<T> parseResultSet(const pqxx::result &) const = 0;

    /**
     * Устанавливает аргументы insert запроса в соответствии со значением полей объекта object.
     */

    virtual void prepareStatementForInsert(pqxx::prepare::invocation &, T &object) const = 0;

    /**
     * Устанавливает аргументы update запроса в соответствии со значением полей объекта object.
     */

    virtual void prepareStatementForUpdate(pqxx::prepare::invocation &, T &object)const = 0;
    DAOFactory parentFactory;
    PooledConnection connection;

public:
    T getByPrimaryKey(std::string_view key) {
        try {
            std::vector<T> list;
            const std::string sql = getSelectQuery() + " WHERE id = $1";
            pqxx::work txn(connection);
            pqxx::result rs = txn.exec_params(sql, key);
            for (const auto& row : rs) {
                list.emplace_back(parseRow<T>(row));
            }
            if (list.empty()) {
                return nullptr;
            }
            if (list.size() > 1) {
                throw PersistException("Received more than one record.");
            }
            return list.front();
        } catch (const std::exception& e) {
            throw PersistException(e.what());
        }
    }
    std::vector<T> getAll() {
        try {
            std::vector<T> list;
            const std::string sql = getSelectAllQuery();
            pqxx::work txn(connection);
            pqxx::result rs = txn.exec(sql);
            for (const auto& row : rs) {
                list.emplace_back(parseRow<T>(row));
            }
            return list;
        } catch (const std::exception& e) {
            throw PersistException(e.what());
        }
    }

    T persist(T object) {
        if (!object.getId().empty()) {
            throw PersistException("Object is already persisted.");
        }
        try {
            // Добавляем запись
            const std::string sql = getCreateQuery();
            pqxx::work txn(connection);
            pqxx::prepare::invocation invoc(txn.prepared(sql));
            prepareStatementForInsert(invoc, object);
            pqxx::result rs = invoc.exec();
            if (rs.affected_rows() != 1) {
                throw PersistException("On persist modify more than 1 record: " + std::to_string(rs.affected_rows()));
            }
            txn.commit();
            // Получаем только что вставленную запись
            const std::string selectSql = getSelectQuery() + " WHERE id = lastval();";
            pqxx::result selectRs = txn.exec(selectSql);
            std::vector<T> list;
            for (const auto& row : selectRs) {
                list.emplace_back(parseRow<T>(row));
            }
            if (list.empty() || list.size() != 1) {
                throw PersistException("Exception on findByPrimaryKey new persist data.");
            }
            return list.front();
        } catch (const std::exception& e) {
            throw PersistException(e.what());
        }
    }
    void update(T object) {
        try {

            // Update the record
            const std::string sql = getUpdateQuery();
            pqxx::work txn(connection);
            pqxx::prepare::invocation invoc(txn.prepared(sql));
            prepareStatementForUpdate(invoc, object);
            pqxx::result rs = invoc.exec();
            if (rs.affected_rows() != 1) {
                throw PersistException("On update modify more than 1 record: " + std::to_string(rs.affected_rows()));
            }
            txn.commit();
        } catch (const std::exception& e) {
            throw PersistException(e.what());
        }
    }

    void remove(T object) {
        try {
            // Check if the object is already persisted
            if (object.getId().empty()) {
                throw PersistException("Object is not persisted.");
            }

            // Delete the record
            const std::string sql = getDeleteQuery() + " WHERE id = " + object.getId();//TODO to string
            pqxx::work txn(connection);
            pqxx::result rs = txn.exec(sql);
            if (rs.affected_rows() != 1) {
                throw PersistException("On delete modify more than 1 record: " + std::to_string(rs.affected_rows()));
            }
            txn.commit();
        } catch (const std::exception& e) {
            throw PersistException(e.what());
        }
    }

public:
    AbstractPQXXDao(const DAOFactory &parentFactory, const PooledConnection &connection) {
        this->parentFactory = parentFactory;
        this->connection = connection;
    }
};


#endif //TASKHIVE_ABSTRACTPQXXDAO_H
