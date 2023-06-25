//
// Created by daniil on 6/18/23.
//
#include "entity/Entity.h"

void Entity::setId(std::string_view id_) {
    this->id = id_;
}

Entity::Entity(std::string_view id) {
    setId(id);
}
