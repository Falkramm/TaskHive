//
// Created by daniil on 7/8/23.
//

#ifndef TASKHIVE_USERSERVICE_H
#define TASKHIVE_USERSERVICE_H
#include <service/service.h>
namespace Service{
    class UserService: public Service<User>{
    public:
        explicit UserService(const std::shared_ptr<PostgresDAOFactory> &factory);

        [[nodiscard]] std::shared_ptr<User> getById(const std::string &id) const override;

        [[nodiscard]] std::vector<std::shared_ptr<User>> getAll() const override;

        [[nodiscard]] std::shared_ptr<User> persist(std::shared_ptr<User> object) const override;

        void remove(std::shared_ptr<User> object) const override;

        void update(std::shared_ptr<User> object) const override;
        std::shared_ptr<User> getByLogin(const std::string &login);
    };

    class UserServiceCreator: public ServiceCreator{
    public:
        [[nodiscard]] boost::any create(std::shared_ptr<PostgresDAOFactory> daoFactory) const override;
    };
}

#endif //TASKHIVE_USERSERVICE_H
