//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_DISPATCHER_H
#define TASKHIVE_DISPATCHER_H

#include <controller/controller.h>
#include <controller/action/actionManagerFactory.h>
#include <controller/action/actionFactory.h>
#include <controller/action/authentication/logOutAction.h>//TODO only for test
#include <memory>
#include <utility>

namespace controller {
    class Dispatcher {
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

        void signOut() {
//        if (getAuthorizedUser() == nullptr)
//            throw new std::runtime_error("The user has already logged out");
//        setAuthorizedUser(nullptr);
            std::shared_ptr<controller::Action::LogoutAction> action = std::make_shared<controller::Action::LogoutAction>();
            process<bool>(action);
        }

        std::vector<std::shared_ptr<Entity::Task> > getTaskList();

        void updateTask(std::shared_ptr<Entity::Task> task);

        void updateTasks(std::vector<std::shared_ptr<Entity::Task> > &tasks);

        void removeTask(std::shared_ptr<Entity::Task> task);

        std::shared_ptr<Entity::Task> persistTask(std::shared_ptr<Entity::Task> task);

        template<typename ActionType, typename... InputType>
        auto process(std::shared_ptr<ActionType> action, InputType... request) -> decltype(action->exec(request...)) {
            std::shared_ptr<Action::ActionManager> actionManager = nullptr;
            try {
                actionManager = Action::ActionManagerFactory::getManager(getFactory());
                return actionManager->execute(action, request...);
            } catch (DAO::PersistException e) {
                // TODO: Handle the exception
            }
            if (actionManager != nullptr) {
                try {
                    actionManager->close();
                } catch (...) {
                    // TODO: Handle the exception
                }
            }
            // Return a default-constructed value of the expected output type
            return decltype(action->exec(request...))();
        }
    };
}


#endif //TASKHIVE_DISPATCHER_H
