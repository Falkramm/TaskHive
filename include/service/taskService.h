//
// Created by daniil on 7/8/23.
//

#ifndef TASKHIVE_TASKSERVICE_H
#define TASKHIVE_TASKSERVICE_H

#include <service/service.h>

namespace Service {
    class TaskService : public Service<Task> {
    public:
        explicit TaskService(const std::shared_ptr<PostgresDAOFactory> &factory);

        [[nodiscard]] std::shared_ptr<Task> getById(const std::string &id) const override;

        [[nodiscard]] std::vector<std::shared_ptr<Task>> getAll() const override;

        [[nodiscard]] std::shared_ptr<Task> persist(std::shared_ptr<Task> object) const override;

        void remove(std::shared_ptr<Task> object) const override;

        void update(std::shared_ptr<Task> object) const override;

        std::vector<std::shared_ptr<Task>> getByUser(std::shared_ptr<User> user);
    };

    class TaskServiceCreator : public ServiceCreator {
    public:
        [[nodiscard]] boost::any create(std::shared_ptr<PostgresDAOFactory> daoFactory) const override;
    };
}
#endif //TASKHIVE_TASKSERVICE_H
