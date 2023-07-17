//
// Created by daniil on 6/18/23.
//

#ifndef TASKHIVE_ENTITY_H
#define TASKHIVE_ENTITY_H

#include <string>
#include <string_view>
#include <ostream>
#include <entity/identified.h>
namespace Entity{
    class Entity: public Identified<std::string>{
    private:
        std::string id;
    public:
        [[nodiscard]] std::string getId() const override{
            return id;
        }

        virtual void setId(std::string_view id_);

        Entity() = default;

        Entity(std::string_view id);

        ~Entity() = default;

        bool operator==(const Entity &rhs) const;

        bool operator!=(const Entity &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Entity &entity);
    };
}

#endif //TASKHIVE_ENTITY_H
