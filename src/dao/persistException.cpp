#include <dao/persistException.h>
namespace DAO{
    PersistException::PersistException() : std::exception() {}

    PersistException::PersistException(std::string_view message) : std::exception(), m_message(message) {}

    PersistException::PersistException(std::string_view message, const std::exception &cause) : std::exception(cause), m_message(message) {}

    PersistException::PersistException(const std::exception &cause) : std::exception(cause) {}

    const char *PersistException::what() const noexcept {
        return m_message.c_str();
    }
};
