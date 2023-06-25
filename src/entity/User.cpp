//
// Created by daniil on 6/18/23.
//
#include "entity/User.h"

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
