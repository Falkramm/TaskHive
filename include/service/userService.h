//
// Created by daniil on 7/8/23.
//

#ifndef TASKHIVE_USERSERVICE_H
#define TASKHIVE_USERSERVICE_H
#include <service/service.h>
namespace Service{
    class UserService: public Service<User>{
    public:
        UserService(const std::shared_ptr<PostgresDAOFactory> &factory) : Service(
                typeid(User).name(), factory) {}

        std::shared_ptr<User> getById(const std::string &id) const override {
            auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
            return dao->getByPrimaryKey(id);
        }

        std::vector<std::shared_ptr<User>> getAll() const override {
            auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
            return dao->getAll();
        }

        std::shared_ptr<User> persist(const std::shared_ptr<User> object) const override {
            auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
            return dao->persist(object);
        }

        void remove(const std::shared_ptr<User> object) const override {
            auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
            dao->remove(object);
        }

        void update(const std::shared_ptr<User> object) const override {
            auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
            dao->update(object);
        }
        std::shared_ptr<User> getByLogin(const std::string &login){
            auto dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(genericDAO);
            return dao->getByLogin(login);
        }
    };

    class UserServiceCreator: public ServiceCreator{
    public:
        boost::any create(std::shared_ptr<PostgresDAOFactory> daoFactory) const override {
            return std::make_shared<UserService>(daoFactory);
        }
    };
}

#endif //TASKHIVE_USERSERVICE_H
