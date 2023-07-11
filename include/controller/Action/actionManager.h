//
// Created by daniil on 7/11/23.
//

#ifndef TASKHIVE_ACTIONMANAGER_H
#define TASKHIVE_ACTIONMANAGER_H
#include <controller/controller.h>
#include <service/serviceFactory.h>
#include <controller/Action/action.h>
#include <controller/Command/command.h>
namespace controller {
    class ActionManager {
    private:
        std::shared_ptr<ServiceFactory> factory;

    public:
        ActionManager(std::shared_ptr<ServiceFactory> factory) : factory(factory) {}

        void execute(std::shared_ptr<Action> action, std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
            action->setFactory(factory);
            action->exec(request, response);
        }

        void close(){
                factory->close();
        }
    };
    class ActionManagerFactory {

    public:
        static std::shared_ptr<ActionManager> getManager(std::shared_ptr<ServiceFactory> factory) {
            return std::make_shared<ActionManager>(factory);
        }
    }
}


#endif //TASKHIVE_ACTIONMANAGER_H
