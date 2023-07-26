//
// Created by daniil on 6/25/23.
//

#ifndef TASKHIVE_POSTGRESUSERDAO_H
#define TASKHIVE_POSTGRESUSERDAO_H
#include <dao/DAO.h>
#include <dao/abstractPQXXDao.h>
#include <utility>
#include <entity/User.h>
namespace DAO{
    class PostgresUserDAO : public AbstractPQXXDao<User, std::string> {
    private:
        static std::string selectQ;
        static std::string selectALlQ;
        static std::string insertQ;
        static std::string updateQ;
        static std::string deleteQ;

        class PersistTask : public User {
        public:
            void setId(std::string_view id) override;
        };

        std::string getSelectQuery() const override;

        std::string getSelectAllQuery() const override;

        std::string getCreateQuery() const override;

        std::string getUpdateQuery() const override;

        std::string getDeleteQuery() const override;

        std::shared_ptr<User> create() override;

        std::vector<std::shared_ptr<User>> parseResultSet(const pqxx::result &rs) const override;

        std::shared_ptr<pqxx::result>
        prepareStatementForInsert(pqxx::work &work, std::shared_ptr<User> object) const override;

        std::shared_ptr<pqxx::result>
        prepareStatementForUpdate(pqxx::work &work, std::shared_ptr<User> object) const override;

    public:
        std::shared_ptr<User> getByLogin(const std::string &login);

    public:
        explicit PostgresUserDAO(std::shared_ptr<PooledConnection> connection_);

    public:
        class UserCreator: public DaoCreator{
        public:
            [[nodiscard]] boost::any create(std::shared_ptr<PooledConnection> pooledConnection)const override;
        };
    };


}
#endif //TASKHIVE_POSTGRESUSERDAO_H
