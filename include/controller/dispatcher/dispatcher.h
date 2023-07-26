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
        static std::shared_ptr<Entity::User> authorizedUser;

        static std::shared_ptr<Service::ServiceFactory> getFactory();

        static std::shared_ptr<Entity::User> getAuthorizedUser();

        static void setAuthorizedUser(std::shared_ptr<Entity::User> user);

    public:
        static void signIn(std::shared_ptr<Entity::User> &user);

        static void signUp(std::shared_ptr<Entity::User> &user);

        static void signOut();

        static std::vector<std::shared_ptr<Entity::Task> > getTaskList();

        static void updateTask(std::shared_ptr<Entity::Task> task);

        static void removeTask(std::shared_ptr<Entity::Task> task);

        static std::shared_ptr<Entity::Task> persistTask(std::shared_ptr<Entity::Task> task);
    };
}


#endif //TASKHIVE_DISPATCHER_H
