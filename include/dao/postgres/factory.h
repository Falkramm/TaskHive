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
class PostgresDAOFactory : public DAOFactory{
private:
    std::shared_ptr<PooledConnection> connection;
    std::unordered_map<std::string_view, std::shared_ptr<DaoCreator>> creators;

public:
    std::shared_ptr<PooledConnection> getConnection() {
        return connection;
    }

    boost::any getDao(const std::string &dtoClass)const override {
        std::shared_ptr<DaoCreator> creator = nullptr;
        if (creators.contains(dtoClass)) {
            creator = creators.find(dtoClass)->second;
        } else {
            throw PersistException("Dao object for " + dtoClass + " not found.");
        }
        return creator->create(connection);
    }
    void close() {
        connection->close();
    }

    PostgresDAOFactory() {
        connection = ConnectionPool::getInstance()->getConnection();
        creators[typeid(User).name()] =  std::make_shared<UserCreator>();
        creators[typeid(Task).name()] =  std::make_shared<TaskCreator>();
    }
protected:
    class UserCreator: public DaoCreator{
    public:
        [[nodiscard]] boost::any create(std::shared_ptr<PooledConnection> pooledConnection)const override {
            return std::make_shared<PostgresUserDAO>(pooledConnection);
        }
    };
    class TaskCreator: public DaoCreator{
    public:
        [[nodiscard]] boost::any create(std::shared_ptr<PooledConnection> pooledConnection)const override{
            return std::make_shared<PostgresTaskDAO>(pooledConnection);
        }
    };
};
#endif //TASKHIVE_FACTORY_H