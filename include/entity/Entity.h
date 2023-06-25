//
// Created by daniil on 6/18/23.
//

#ifndef TASKHIVE_ENTITY_H
#define TASKHIVE_ENTITY_H

#include <string>
#include <string_view>
#include "entity/identified.h"
class Entity: public Identified<std::string>{
private:
    std::string id;
public:
    [[nodiscard]] std::string getId() const override{
        return id;
    }

    virtual void setId(std::string_view id_);

    Entity() = default;

    explicit Entity(std::string_view id);

    ~Entity() = default;

};


#endif //TASKHIVE_ENTITY_H
