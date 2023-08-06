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

namespace DAO {
    class PostgresDAOFactory : public DAOFactory {
    private:
        std::shared_ptr<PooledConnection> connection;
        static std::unordered_map<std::string, std::shared_ptr<DaoCreator>> creators;

    public:
        std::shared_ptr<PooledConnection> getConnection();

        boost::any getDao(const std::string &dtoClass) const override;

        void close() const override;

        static void init();

        PostgresDAOFactory();
    };

}
#endif //TASKHIVE_FACTORY_H
