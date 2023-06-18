//
// Created by daniil on 6/18/23.
//
#include "entity/Entity.h"

std::string_view Entity::getId() const {
    return id;
}

void Entity::setId(std::string_view id_) {
    this->id = id_;
}

Entity::Entity(std::string_view id) {
    setId(id);
}
