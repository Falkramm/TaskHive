//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_DAOFACTORY_H
#define TASKHIVE_DAOFACTORY_H

#include <string_view>
#include <dao/DAO.h>
#include <dao/genericDao.h>
#include <memory>
#include <type_traits>
#include <dao/connectionPool/connectionPool.h>
#include <boost/any.hpp>
namespace DAO{
    class DAOFactory {
    public:
        virtual ~DAOFactory() = default;


        virtual boost::any getDao(const std::string &dtoClass) const = 0;//TODO need to recode
        virtual void close() const = 0;
    };

    class DaoCreator {
    public:
    //        template<typename T, typename PK>
    //        requires std::is_same<T, Identified<PK>>::value
    //        std::shared_ptr<GenericDAO<T, PK>>
        virtual boost::any create(std::shared_ptr<PooledConnection> pooledConnection) const = 0;//TODO need to recode
    };
}
#endif //TASKHIVE_DAOFACTORY_H
