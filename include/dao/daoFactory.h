//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_DAOFACTORY_H
#define TASKHIVE_DAOFACTORY_H

#include <string_view>
#include "genericDao.h"

#include <memory>
#include <type_traits>
#include "connectionPool/connectionPool.h"


class DAOFactory {
public:
    virtual ~DAOFactory() {}
    class DaoCreator {
    public:
        template<typename T, typename PK>
        requires std::is_same<T, Identified<PK>>::value
        GenericDAO<T, PK> create(PooledConnection context);
    };
    template<typename T, typename PK>
    requires std::is_same<T, Identified<PK>>::value
    std::shared_ptr<GenericDAO<T, PK>> getDAOInstance(PooledConnection &connection);
};





#endif //TASKHIVE_DAOFACTORY_H
