//
// Created by daniil on 6/24/23.
//

#ifndef TASKHIVE_POSTGRESDAOFACTORY_H
#define TASKHIVE_POSTGRESDAOFACTORY_H

#include <dao/daoFactory.h>
#include <dao/connectionPool/connectionPool.h>
#include <unordered_map>
#include <dao/abstractPQXXDao.h>
template <typename ValueType, typename RecordType>
class PostgresDAOFactory: public DAOFactory<ValueType, RecordType> {
public:
    std::shared_ptr<GenericDAO<ValueType, RecordType>> getDAOInstance(PooledConnection& connection)
    {
        return std::make_shared<AbstractPQXXDao<ValueType, RecordType>>(connection);
    }
};


#endif //TASKHIVE_POSTGRESDAOFACTORY_H
