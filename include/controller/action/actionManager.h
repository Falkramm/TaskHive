//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_ACTIONMANAGER_H
#define TASKHIVE_ACTIONMANAGER_H

#include <controller/action/action.h>

#include <utility>

namespace controller::Action {
    class ActionManager {
    private:
        std::shared_ptr<Service::ServiceFactory> factory;

    public:
        ActionManager(std::shared_ptr<Service::ServiceFactory> factory_);

        void execute(std::shared_ptr<GenericAction> action, boost::any request, boost::any response);

        void close();
    };
}


#endif //TASKHIVE_ACTIONMANAGER_H
