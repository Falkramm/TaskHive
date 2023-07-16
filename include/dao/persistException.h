//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_PERSISTEXCEPTION_H
#define TASKHIVE_PERSISTEXCEPTION_H


#include <exception>
#include <string>
#include <stdexcept>
#include <string>

class PersistException : public std::exception {
public:
    PersistException() : std::exception() {}

    PersistException(std::string_view message) : std::exception(), m_message(message) {}

    PersistException(std::string_view message, const std::exception& cause) : std::exception(cause), m_message(message) {}

    explicit PersistException(const std::exception& cause) : std::exception(cause) {}

    [[nodiscard]] const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};


#endif //TASKHIVE_PERSISTEXCEPTION_H
