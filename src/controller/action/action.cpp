#include <controller/action/action.h>

void controller::Action::GenericAction::setAuthorizedUser(std::shared_ptr<Entity::User> authorizedUser_) {
    this->authorizedUser = std::move(authorizedUser_);
}

std::string_view controller::Action::GenericAction::getName() {
    return name;
}

void controller::Action::GenericAction::setName(std::string_view name_) {
    this->name = name_;
}

void controller::Action::GenericAction::setFactory(std::shared_ptr<Service::ServiceFactory> factory_) {
    this->factory = std::move(factory_);
}

std::shared_ptr<Entity::User> controller::Action::GenericAction::getAuthorizedUser() const {
    return authorizedUser;
}
