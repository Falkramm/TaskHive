//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_ABSTRACTPQXXDAO_H
#define TASKHIVE_ABSTRACTPQXXDAO_H
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <pqxx/pqxx>
#include <utility>
#include <vector>
#include <genericDao.h>
#include <identified.h>
#include <connectionPool.h>
#include <persistException.h>
#include <daoFactory.h>

template<typename T, typename PK> requires DerivedFromIdentified<T, PK>
class AbstractPQXXDao : public GenericDAO<T, PK>, public std::enable_shared_from_this<AbstractPQXXDao<T, PK>> {
public:
    AbstractPQXXDao(std::shared_ptr<PooledConnection> connection) : connection(std::move(connection)) {}

    /**
     * Возвращает sql запрос для получения одной записи.
     * <p/>
     * SELECT * FROM [Table]
     */
    [[nodiscard]] virtual std::string getSelectQuery() const = 0;

    /**
     * Возвращает sql запрос для получения всех записей.
     * <p/>
     * SELECT * FROM [Table]
     */
    [[nodiscard]] virtual std::string getSelectAllQuery() const = 0;

    /**
     * Возвращает sql запрос для вставки новой записи в базу данных.
     * <p/>
     * INSERT INTO [Table] ([column, column, ...]) VALUES (?, ?, ...);
     */
    [[nodiscard]] virtual std::string getCreateQuery() const = 0;

    /**
     * Возвращает sql запрос для обновления записи.
     * <p/>
     * UPDATE [Table] SET [column = ?, column = ?, ...] WHERE id = ?;
     */
    [[nodiscard]] virtual std::string getUpdateQuery() const = 0;

    /**
     * Возвращает sql запрос для удаления записи из базы данных.
     * <p/>
     * DELETE FROM [Table] WHERE id= ?;
     */
    [[nodiscard]] virtual std::string getDeleteQuery() const = 0;

    /**
     * Разбирает ResultSet и возвращает список объектов соответствующих содержимому ResultSet.
     */
protected:

    virtual std::vector<std::shared_ptr<T>> parseResultSet(const pqxx::result &) const = 0;

    /**
     * Устанавливает аргументы insert запроса в соответствии со значением полей объекта object.
     */

    virtual std::shared_ptr<pqxx::result>
    prepareStatementForInsert(pqxx::work &work, std::shared_ptr<T> object) const = 0;

    /**
     * Устанавливает аргументы update запроса в соответствии со значением полей объекта object.
     */

    virtual std::shared_ptr<pqxx::result>
    prepareStatementForUpdate(pqxx::work &work, std::shared_ptr<T> object) const = 0;

//    std::shared_ptr<DAOFactory> parentFactory;
    std::shared_ptr<PooledConnection> connection;

public:
    std::shared_ptr<T> getByPrimaryKey(const PK &key) override {
        try {
            std::vector<std::shared_ptr<T>> list;
            pqxx::work txn(*connection);
            const std::string &sql = getSelectQuery() + " WHERE id = $1;";
            pqxx::result rs = txn.exec_params(sql, key);
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

    std::vector<std::shared_ptr<T>> getAll() override {
        try {
            std::cout << "Start get All\n";
            std::vector<std::shared_ptr<T>> list;
            pqxx::work txn(*connection);
            std::string sql = getSelectAllQuery();
            pqxx::result rs = txn.exec(sql);
            txn.commit();
            std::cout << "Exec\n";
            list = parseResultSet(rs);
            std::cout << "Parsed\n";
            return list;
        } catch (const std::exception &e) {
            throw PersistException(e.what());
        }
    }

    std::shared_ptr<T> persist(std::shared_ptr<T> object) override {
        if (!object->getId().empty()) {
            throw PersistException("Object is already persisted.");
        }
        try {
            // Добавляем запись
            std::string sql = getCreateQuery();
            pqxx::work txn(*connection);
            std::cout << "Start\n";
            std::shared_ptr<pqxx::result> rs = prepareStatementForInsert(txn, object);
            std::cout << "Inserted\n";
            if (rs->affected_rows() != 1) {
                txn.abort();
                throw PersistException("On persist modify more than 1 record: " + std::to_string(rs->affected_rows()));
            }
            txn.commit();
            // Получаем только что вставленную запись
            const std::string selectSql = getSelectQuery() + " WHERE id = lastval();";
            pqxx::work choose(*connection);
            pqxx::result selectRs = choose.exec(selectSql);
            std::vector<std::shared_ptr<T>> list;
            list = parseResultSet(selectRs);
            if (list.empty() || list.size() != 1) {
                throw PersistException("Exception on findByPrimaryKey new persist data.");
            }
            return list.front();
        } catch (const std::exception &e) {
            throw PersistException(e.what());
        }
    }

    void update(std::shared_ptr<T> object) override {
        try {

            // Update the record
            const std::string sql = getUpdateQuery();
            pqxx::work txn(*connection);
            std::shared_ptr<pqxx::result> rs = prepareStatementForUpdate(txn, object);
            if (rs->affected_rows() != 1) {
                txn.abort();
                throw PersistException("On update modify more than 1 record: " + std::to_string(rs->affected_rows()));
            }
            txn.commit();
        } catch (const std::exception &e) {
            throw PersistException(e.what());
        }
    }

    void remove(std::shared_ptr<T> object) override {
        try {
            // Check if the object is already persisted
            if (object->getId().empty()) {
                throw PersistException("Object is not persisted.");
            }

            // Delete the record
            pqxx::work txn(*connection);
            std::string sql = getSelectQuery();
            pqxx::result rs = txn.exec_params(sql, object->getId());
            if (rs.affected_rows() != 1) {
                throw PersistException("On delete modify more than 1 record: " + std::to_string(rs.affected_rows()));
            }
            txn.commit();
        } catch (const std::exception &e) {
            throw PersistException(e.what());
        }
    }


};


#endif //TASKHIVE_ABSTRACTPQXXDAO_H
