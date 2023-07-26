#include <controller/dispatcher/dispatcher.h>

#include <utility>

namespace controller {
    std::shared_ptr<Service::ServiceFactory> Dispatcher::getFactory() {
        return std::make_shared<Service::ServiceFactory>();
    }

    std::shared_ptr<Entity::User> Dispatcher::getAuthorizedUser() {
        return authorizedUser;
    }

    void Dispatcher::setAuthorizedUser(std::shared_ptr<Entity::User> user) {
        authorizedUser = std::move(user);
    }

    void Dispatcher::signIn(std::shared_ptr<Entity::User> &user) {
        if (getAuthorizedUser() != nullptr)
            throw std::runtime_error("The user is already logged in");
        auto factory = getFactory();
        auto userService = boost::any_cast<std::shared_ptr<Service::UserService>>(
                factory->getService(typeid(Entity::User).name()));
        std::string password = user->getPassword();
        try {
            user = userService->getByLogin(user->getLogin());
        } catch (...) {
            throw std::runtime_error("The login or password is not recognized");
        }
        if (user->getPassword() != password)
            throw std::runtime_error("The login or password is not recognized");
        setAuthorizedUser(user);
    }

    void Dispatcher::updateTask(std::shared_ptr<Entity::Task> task) {
        if (getAuthorizedUser() == nullptr)
            throw new std::runtime_error("The user is not logged in");
        auto factory = getFactory();
        auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(
                factory->getService(typeid(Entity::Task).name()));
        taskService->update(task);
    }

    void Dispatcher::signUp(std::shared_ptr<Entity::User> &user) {
        if (getAuthorizedUser() != nullptr)
            throw std::runtime_error("The user is already logged in");
        auto factory = getFactory();
        auto userService = boost::any_cast<std::shared_ptr<Service::UserService>>(
                factory->getService(typeid(Entity::User).name()));
        std::string password = user->getPassword();
        if (userService->getByLogin(user->getLogin()) != nullptr)
            throw new std::runtime_error("This login is already occupied");
        user = userService->persist(user);
    }

    void Dispatcher::signOut() {
        if (getAuthorizedUser() != nullptr)
            throw new std::runtime_error("The user has already logged out");
        setAuthorizedUser(nullptr);
    }

    std::vector<std::shared_ptr<Entity::Task> > Dispatcher::getTaskList() {
        if (getAuthorizedUser() == nullptr)
            throw new std::runtime_error("The user is not logged in");
        auto factory = getFactory();
        auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(
                factory->getService(typeid(Entity::Task).name()));
        return taskService->getByUser(getAuthorizedUser());
    }
    void Dispatcher::removeTask(std::shared_ptr<Entity::Task> task) {
        if (getAuthorizedUser() == nullptr)
            throw new std::runtime_error("The user is not logged in");
        auto factory = getFactory();
        auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(
                factory->getService(typeid(Entity::Task).name()));
        taskService->remove(task);
    }
    std::shared_ptr<Entity::Task> Dispatcher::persistTask(std::shared_ptr<Entity::Task> task) {
        if (getAuthorizedUser() == nullptr)
            throw new std::runtime_error("The user is not logged in");
        task->setKey(getAuthorizedUser()->getId());
        auto factory = getFactory();
        auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(
                factory->getService(typeid(Entity::Task).name()));
        return taskService->persist(task);//TODO need to check for correct persist in DAO
    }
    std::shared_ptr<Entity::User> Dispatcher::authorizedUser = nullptr;
}