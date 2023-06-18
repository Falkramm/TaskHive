//
// Created by daniil on 6/18/23.
//

#ifndef TASKHIVE_USER_H
#define TASKHIVE_USER_H

#include "Entity.h"

class User : public Entity {
private:
    std::string login;
    std::string password;
public:
    [[nodiscard]] std::string_view getLogin() const;

    void setLogin(std::string_view login);

    [[nodiscard]] std::string_view getPassword() const;

    void setPassword(std::string_view password);

};


#endif //TASKHIVE_USER_H
