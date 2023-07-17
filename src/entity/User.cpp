//
// Created by daniil on 6/18/23.
//
#include <entity/User.h>
namespace Entity{
    std::string User::getLogin() const {
        return login;
    }

    void User::setLogin(std::string_view login) {
        User::login = login;
    }

    std::string User::getPassword() const {
        return password;
    }

    void User::setPassword(std::string_view password) {
        User::password = password;
    }

    bool User::operator==(const User &rhs) const {
        return static_cast<const Entity &>(*this) == static_cast<const Entity &>(rhs) &&
               login == rhs.login &&
               password == rhs.password;
    }

    bool User::operator!=(const User &rhs) const {
        return !(rhs == *this);
    }

    User::User(std::string_view id, std::string_view login, std::string_view password) : Entity(id),
                                                                                                    login(login),
                                                                                                    password(password) {}

    User::User(std::string_view login, std::string_view password) : login(login), password(password) {}

    std::ostream &operator<<(std::ostream &os, const User &user) {
        os << static_cast<const Entity &>(user) << " login: " << user.login << " password: " << user.password;
        return os;
    }
}
