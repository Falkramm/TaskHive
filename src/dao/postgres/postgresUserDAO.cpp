#include <dao/postgres/postgresUserDAO.h>
namespace DAO{
    std::string PostgresUserDAO::getSelectQuery() const {
    return selectQ;
    }
    std::string PostgresUserDAO::getSelectAllQuery() const {
    return selectALlQ;
    }
    std::string PostgresUserDAO::getCreateQuery() const {
        return insertQ;
    }

    std::string PostgresUserDAO::getUpdateQuery() const {
        return updateQ;
    }

    std::string PostgresUserDAO::getDeleteQuery() const {
        return deleteQ;
    }

    std::shared_ptr<User> PostgresUserDAO::create() {
        std::shared_ptr<User> user;
        return AbstractPQXXDao<User, std::string>::persist(std::move(user));
    }

    std::vector<std::shared_ptr<User>> PostgresUserDAO::parseResultSet(const pqxx::result &rs) const {
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

    std::shared_ptr<pqxx::result>
    PostgresUserDAO::prepareStatementForInsert(pqxx::work &work, std::shared_ptr<User> object) const {
        auto result = std::make_shared<pqxx::result>(work.exec_params(getCreateQuery(),
                                                                      object->getLogin(),
                                                                      object->getPassword()));
        return result;
    }

    std::shared_ptr<pqxx::result>
    PostgresUserDAO::prepareStatementForUpdate(pqxx::work &work, std::shared_ptr<User> object) const {
        auto result = std::make_shared<pqxx::result>(work.exec_params(getUpdateQuery(),
                                                                      object->getLogin(),
                                                                      object->getPassword(),
                                                                      object->getId()));
        return result;
    }

    std::shared_ptr<User> PostgresUserDAO::getByLogin(const std::string &login) {
        try {
            std::vector<std::shared_ptr<User>> list;

            pqxx::work txn(*connection);
            pqxx::result rs = txn.exec_params(getSelectQuery() + " WHERE login = $1;", login);
            list = parseResultSet(rs);
            if (list.empty() || list.size() > 1) {
                throw PersistException("Received more than one record.");
            }
            txn.commit();
            return std::move(list.front());
        } catch (const std::exception &e) {
            throw PersistException(e.what());
        }
    }

    PostgresUserDAO::PostgresUserDAO(std::shared_ptr<PooledConnection> connection_)
            : AbstractPQXXDao<User, std::string>(std::move(connection_)) {}

    void PostgresUserDAO::PersistTask::setId(std::string_view id) {
        User::setId(id);
    }

    std::string PostgresUserDAO::selectQ = "SELECT * FROM customers ";
    std::string PostgresUserDAO::selectALlQ = "SELECT * FROM customers;";
    std::string PostgresUserDAO::insertQ = "INSERT INTO customers (login, password) \nVALUES ($1, $2);";
    std::string PostgresUserDAO::updateQ = "UPDATE customers SET login=$1, password=$2 WHERE id= $3;";
    std::string PostgresUserDAO::deleteQ = "DELETE FROM customers WHERE id=$1;";

    boost::any PostgresUserDAO::UserCreator::create(std::shared_ptr<PooledConnection> pooledConnection) const {
        return std::make_shared<PostgresUserDAO>(pooledConnection);
    }
}