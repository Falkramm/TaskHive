//
// Created by daniil on 8/10/23.
//

#include "controller/action/actionManager.h"

#include <utility>

controller::Action::ActionManager::ActionManager(std::shared_ptr<Service::ServiceFactory> factory_) {
    this->factory = std::move(factory_);
}

void controller::Action::ActionManager::execute(std::shared_ptr<GenericAction> action, boost::any request, boost::any response) {
    action->setFactory(factory);
    action->exec(std::move(request), std::move(response));
}

void controller::Action::ActionManager::close() {
    factory->close();
}
