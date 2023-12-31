//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_DISPATCHER_H
#define TASKHIVE_DISPATCHER_H

#include <controller/controller.h>
#include <memory>

namespace controller {
    class Dispatcher {
    private:
        std::shared_ptr<Entity::User> authorizedUser;
    public:
        Dispatcher();

    private:
        std::shared_ptr<Service::ServiceFactory> getFactory();

        std::shared_ptr<Entity::User> getAuthorizedUser();

        void setAuthorizedUser(std::shared_ptr<Entity::User> user);

    public:
        bool isAuthorized();
        void signIn(std::shared_ptr<Entity::User> &user);

        void signUp(std::shared_ptr<Entity::User> &user);

        void signOut();

        std::vector<std::shared_ptr<Entity::Task> > getTaskList();

        void updateTask(std::shared_ptr<Entity::Task> task);
        void updateTasks(std::vector<std::shared_ptr<Entity::Task> > &tasks);
        void removeTask(std::shared_ptr<Entity::Task> task);

        std::shared_ptr<Entity::Task> persistTask(std::shared_ptr<Entity::Task> task);
    };
}


#endif //TASKHIVE_DISPATCHER_H
