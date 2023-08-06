//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_PERSISTEXCEPTION_H
#define TASKHIVE_PERSISTEXCEPTION_H


#include <exception>
#include <string>
#include <stdexcept>
#include <string>
#include <dao/DAO.h>
namespace DAO{
    class PersistException : public std::exception {
    public:
        PersistException();

        PersistException(std::string_view message);

        PersistException(std::string_view message, const std::exception& cause);

        explicit PersistException(const std::exception& cause);

        [[nodiscard]] const char* what() const noexcept override;

    private:
        std::string m_message;
    };
}

#endif //TASKHIVE_PERSISTEXCEPTION_H
