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
        static std::shared_ptr<Service::ServiceFactory> getFactory(){
            return std::make_shared<Service::ServiceFactory>();
        }

        static const std::shared_ptr<Entity::User> getAuthorizedUser(){
            return authorizedUser;
        }
        static void setAuthorizedUser(std::shared_ptr<Entity::User> user){
            authorizedUser = user;
        }
    public:
        static void signIn(std::shared_ptr<Entity::User> &user){
            if(getAuthorizedUser() != nullptr)
                throw std::runtime_error("The user is already logged in");
            auto factory = getFactory();
            auto userService = boost::any_cast<std::shared_ptr<Service::UserService>>(factory->getService(typeid(Entity::User).name()));
            std::string password = user->getPassword();
            try{
                user = userService->getByLogin(user->getLogin());
            } catch(...){
                throw std::runtime_error("The login or password is not recognized");
            }
            if(user->getPassword() != password)
                throw std::runtime_error("The login or password is not recognized");
            setAuthorizedUser(user);
        }
        static void signUp(std::shared_ptr<Entity::User> &user){
            if(getAuthorizedUser() != nullptr)
                throw std::runtime_error("The user is already logged in");
            auto factory = getFactory();
            auto userService = boost::any_cast<std::shared_ptr<Service::UserService>>(factory->getService(typeid(Entity::User).name()));
            std::string password = user->getPassword();
            if(userService->getByLogin(user->getLogin()) != nullptr)
                throw new std::runtime_error("This login is already occupied");
            user = userService->persist(user);
        }
        static void signOut(){
            if(getAuthorizedUser() != nullptr)
                throw new std::runtime_error("The user has already logged out");
            setAuthorizedUser(nullptr);
        }
        static std::vector<std::shared_ptr<Entity::Task> > getTaskList(){
            if(getAuthorizedUser() == nullptr)
                throw new std::runtime_error("The user is not logged in");
            auto factory = getFactory();
            auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(factory->getService(typeid(Entity::Task).name()));
            return taskService->getByUser(getAuthorizedUser());
        }
        static void updateTask(std::shared_ptr<Entity::Task> task){
            if(getAuthorizedUser() == nullptr)
                throw new std::runtime_error("The user is not logged in");
            auto factory = getFactory();
            auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(factory->getService(typeid(Entity::Task).name()));
            taskService->update(task);
        }
        static void removeTask(std::shared_ptr<Entity::Task> task){
            if(getAuthorizedUser() == nullptr)
                throw new std::runtime_error("The user is not logged in");
            auto factory = getFactory();
            auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(factory->getService(typeid(Entity::Task).name()));
            taskService->remove(task);
        }
        static std::shared_ptr<Entity::Task> persistTask(std::shared_ptr<Entity::Task> task){
            if(getAuthorizedUser() == nullptr)
                throw new std::runtime_error("The user is not logged in");
            task->setKey(getAuthorizedUser()->getId());
            auto factory = getFactory();
            auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(factory->getService(typeid(Entity::Task).name()));
            return taskService->persist(task);//TODO need to check for correct persist in DAO
        }
    };
    std::shared_ptr<Entity::User> Dispatcher::authorizedUser = nullptr;
}


#endif //TASKHIVE_DISPATCHER_H
