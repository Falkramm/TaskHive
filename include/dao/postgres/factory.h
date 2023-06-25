//
// Created by daniil on 6/25/23.
//

#ifndef TASKHIVE_FACTORY_H
#define TASKHIVE_FACTORY_H

#include <dao/daoFactory.h>
#include <dao/connectionPool/connectionPool.h>
#include <unordered_map>
#include <dao/abstractPQXXDao.h>
#include <entity/User.h>
#include <dao/postgres/postgresUserDAO.h>
#include <dao/postgres/postgresTaskDAO.h>
#include <dao/postgres/postgresFactory.h>
class PostgresDAOFactory : public DAOFactory {
private:
    std::shared_ptr<PooledConnection> connection;
    std::unordered_map<std::string_view, std::unique_ptr<DaoCreator>> creators;

public:
    std::shared_ptr<PooledConnection> getConnection() {
        return connection;
    }

    template<typename T, typename PK>
    requires DerivedFromIdentified<T, PK>
    GenericDAO<T, PK> getDao(const std::string &dtoClass) {
        std::unique_ptr<DAOFactory::DaoCreator> creator;
        if (creators.contains(dtoClass)) {
            creator = std::move(creators[dtoClass]);
        } else {
            throw PersistException("Dao object for " + dtoClass + " not found.");
        }
        return creator->create<T, PK>(connection);
    }
    void close() {
        connection->close();
    }

    PostgresDAOFactory() {
        connection = ConnectionPool::getInstance()->getConnection();
        creators[typeid(User).name()] =  std::make_unique<UserCreator>();
        creators[typeid(Task).name()] =  std::make_unique<TaskCreator>();
    }
protected:
    class UserCreator: public DaoCreator{
    public:
        std::shared_ptr<PostgresUserDAO> create(std::shared_ptr<PostgresDAOFactory> factory, std::shared_ptr<PooledConnection> pooledConnection){
            return std::make_shared<PostgresUserDAO>(factory, pooledConnection);
        }
    };
    class TaskCreator: public DaoCreator{
    public:
        std::shared_ptr<PostgresTaskDAO> create(std::shared_ptr<PostgresDAOFactory> factory, std::shared_ptr<PooledConnection> pooledConnection){
            return std::make_shared<PostgresTaskDAO>(factory, pooledConnection);
        }
    };
};
#endif //TASKHIVE_FACTORY_H
