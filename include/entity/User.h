//
// Created by daniil on 6/18/23.
//

#ifndef TASKHIVE_USER_H
#define TASKHIVE_USER_H

#include <ostream>
#include "Entity.h"

class User : public Entity {
private:
    std::string login;
    std::string password;
public:
    [[nodiscard]] std::string getLogin() const;

    void setLogin(std::string_view login);

    [[nodiscard]] std::string getPassword() const;

    void setPassword(std::string_view password);

    User() = default;

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;

    User(std::string_view id,std::string_view login,std::string_view password);

    User(std::string_view login,std::string_view password);

    friend std::ostream &operator<<(std::ostream &os, const User &user);
};


#endif //TASKHIVE_USER_H
