#include <service/userService.h>
namespace Service{
    UserService::UserService(const std::shared_ptr<PostgresDAOFactory> &factory) : Service(
            typeid(User).name(), factory) {}

    std::shared_ptr<User> UserService::getById(const std::string &id) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
        return dao->getByPrimaryKey(id);
    }

    std::vector<std::shared_ptr<User>> UserService::getAll() const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
        return dao->getAll();
    }

    std::shared_ptr<User> UserService::persist(const std::shared_ptr<User> object) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
        return dao->persist(object);
    }

    void UserService::remove(const std::shared_ptr<User> object) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
        dao->remove(object);
    }

    void UserService::update(const std::shared_ptr<User> object) const {
        auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
        dao->update(object);
    }

    std::shared_ptr<User> UserService::getByLogin(const std::string &login) {
        auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
        return dao->getByLogin(login);
    }

    boost::any UserServiceCreator::create(std::shared_ptr<PostgresDAOFactory> daoFactory) const {
        return std::make_shared<UserService>(daoFactory);
    }
}