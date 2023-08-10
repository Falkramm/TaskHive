//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_ACTIONMANAGERFACTORY_H
#define TASKHIVE_ACTIONMANAGERFACTORY_H

#include <controller/action/actionManager.h>
#include <unordered_map>
namespace controller::Action {
    class ActionManagerFactory {
    public:
        static std::shared_ptr<ActionManager> getManager(std::shared_ptr<Service::ServiceFactory> factory);
    };
}

#endif //TASKHIVE_ACTIONMANAGERFACTORY_H
