//
// Created by daniil on 6/18/23.
//

#ifndef TASKHIVE_ENTITY_H
#define TASKHIVE_ENTITY_H

#include <string>
#include <string_view>
class Entity {
private:
    std::string id;
public:
    [[nodiscard]] std::string_view getId() const;

    void setId(std::string_view id_);

    Entity() = default;

    explicit Entity(std::string_view id);

    ~Entity() = default;

};


#endif //TASKHIVE_ENTITY_H
