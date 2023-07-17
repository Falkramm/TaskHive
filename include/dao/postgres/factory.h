//
// Created by daniil on 6/25/23.
//

#ifndef TASKHIVE_FACTORY_H
#define TASKHIVE_FACTORY_H
#include <dao/DAO.h>
#include <dao/daoFactory.h>
#include <dao/connectionPool/connectionPool.h>
#include <unordered_map>
#include <dao/abstractPQXXDao.h>
#include <entity/User.h>
#include <dao/postgres/postgresUserDAO.h>
#include <dao/postgres/postgresTaskDAO.h>
namespace DAO{
    class PostgresDAOFactory : public DAOFactory{
    private:
        std::shared_ptr<PooledConnection> connection;
        static std::unordered_map<std::string, std::shared_ptr<DaoCreator>> creators;

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
        void close()const override{
            connection->close();
        }
        static void init(){//TODO need to init;
            creators[typeid(User).name()] =  std::make_shared<UserCreator>();
            creators[typeid(Task).name()] =  std::make_shared<TaskCreator>();
        }
        PostgresDAOFactory() {
            connection = ConnectionPool::getInstance()->getConnection();
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
    std::unordered_map<std::string, std::shared_ptr<DaoCreator>> PostgresDAOFactory::creators;
}
#endif //TASKHIVE_FACTORY_H
