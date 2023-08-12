#include <controller/dispatcher/dispatcher.h>

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
        std::cout << "Now user: " << getAuthorizedUser() << '\n';
        if (getAuthorizedUser() != nullptr) {
            std::cout << "The user is already logged in\n" ;
            throw std::runtime_error("The user is already logged in");
        }
        auto factory = getFactory();
        auto userService = boost::any_cast<std::shared_ptr<Service::UserService>>(
                factory->getService(typeid(Entity::User).name()));
        std::string password = user->getPassword();
        try {
            user = userService->getByLogin(user->getLogin());
        } catch (...) {
            std::cout << "The login or password is not recognized\n";
            throw std::runtime_error("The login or password is not recognized");
        }
        if (user == nullptr || user->getPassword() != password) {
            std::cout << "The login or password is not recognized\n";
            throw std::runtime_error("The login or password is not recognized");
        }
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
        std::cout << *user << '\n';
        if (getAuthorizedUser() != nullptr)
            throw std::runtime_error("The user is already logged in");
        auto factory = getFactory();
        auto userService = boost::any_cast<std::shared_ptr<Service::UserService>>(
                factory->getService(typeid(Entity::User).name()));
        std::cout << *user << '\n';
        if (userService->getByLogin(user->getLogin()) != nullptr)
            throw new std::runtime_error("This login is already occupied");
        user = userService->persist(user);
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

    Dispatcher::Dispatcher(): authorizedUser(nullptr){}

    bool Dispatcher::isAuthorized() {
        return getAuthorizedUser() != nullptr;
    }

    void Dispatcher::updateTasks(std::vector<std::shared_ptr<Entity::Task>> &tasks) {
        if (getAuthorizedUser() == nullptr)
            throw new std::runtime_error("The user is not logged in");
        auto factory = getFactory();
        auto taskService = boost::any_cast<std::shared_ptr<Service::TaskService>>(
                factory->getService(typeid(Entity::Task).name()));
        for(auto &task : tasks){
            std::cout << *task << '\n';
            try {
                if (task->getId().empty()) {
                    task->setKey(getAuthorizedUser()->getId());
                    try {
                        *task = *taskService->persist(task);
                    }catch (...){
                        std::cout << "Can't persist\n";
                    }
                } else
                    taskService->update(task);
            } catch(std::exception e){
                std::cout << "Can't update Task " << e.what() << '\n';
            }
        }
    }
}