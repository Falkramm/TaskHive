//
// Created by daniil on 8/10/23.
//

#include "controller/action/actionManagerFactory.h"

std::shared_ptr<controller::Action::ActionManager>
controller::Action::ActionManagerFactory::getManager(std::shared_ptr<Service::ServiceFactory> factory) {
    return std::make_shared<ActionManager>(factory);
}
