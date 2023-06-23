//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_DAOFACTORY_H
#define TASKHIVE_DAOFACTORY_H

#include <string_view>
#include "genericDao.h"

#include <memory>
#include <type_traits>


template<typename Connection>
class DAOFactory {
public:
    /** Returns an object for managing the persistent state of an object */
    template<class T, class PK>
    std::unique_ptr<GenericDAO<T, PK>> getDao(std::type_info const &dtoClass) const = delete;

    virtual ~DAOFactory() = default;
};

template<typename Connection, typename T>
concept DaoCreator = requires(Connection conn) {
    { std::declval<T>().create(conn) } -> std::same_as<std::unique_ptr<GenericDAO<T, std::string_view>>>;
};

#endif //TASKHIVE_DAOFACTORY_H
