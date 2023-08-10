//
// Created by daniil on 8/10/23.
//

#include "controller/action/actionFactory.h"

void controller::Action::ActionManagerFactory::init() {
    //TODO add creator by uri
}

std::shared_ptr<controller::Action::GenericAction> controller::Action::ActionManagerFactory::getAction(std::string_view uri) {
    std::shared_ptr<Action::ActionCreator> creator = nullptr;
    if (creators->contains(uri)) {
        creator = creators->find(uri)->second;
    } else {
        throw std::runtime_error("No one any action by that uri");//TODO
    }
    return creator->create();
}
