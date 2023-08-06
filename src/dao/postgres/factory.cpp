#include <dao/postgres/factory.h>

namespace DAO {

    std::shared_ptr<PooledConnection> PostgresDAOFactory::getConnection() {
        return connection;
    }

    boost::any PostgresDAOFactory::getDao(const std::string &dtoClass) const {
        std::shared_ptr<DaoCreator> creator = nullptr;
        if (creators.contains(dtoClass)) {
            creator = creators.find(dtoClass)->second;
        } else {
            throw PersistException("Dao object for " + dtoClass + " not found.");
        }
        return creator->create(connection);
    }

    void PostgresDAOFactory::close() const {
        connection->close();
    }

    void PostgresDAOFactory::init() {//TODO need to init;
        creators[typeid(User).name()] = std::make_shared<PostgresUserDAO::UserCreator>();
        creators[typeid(Task).name()] = std::make_shared<PostgresTaskDAO::TaskCreator>();
    }

    PostgresDAOFactory::PostgresDAOFactory() {
        connection = ConnectionPool::getInstance()->getConnection();
    }

    std::unordered_map<std::string, std::shared_ptr<DaoCreator>> PostgresDAOFactory::creators;
}
