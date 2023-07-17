//
// Created by daniil on 6/18/23.
//
#include <entity/Entity.h>
namespace Entity{
    void Entity::setId(std::string_view id_) {
        this->id = id_;
    }

    Entity::Entity(std::string_view id) {
        setId(id);
    }

    bool Entity::operator==(const Entity &rhs) const {
        return id == rhs.id;
    }

    bool Entity::operator!=(const Entity &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Entity &entity) {
        os << " id: " << entity.id;
        return os;
    }
}
