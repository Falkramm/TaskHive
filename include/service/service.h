//
// Created by daniil on 7/5/23.
//

#ifndef TASKHIVE_SERVICE_H
#define TASKHIVE_SERVICE_H

#include <log4cpp/Category.hh>
#include <boost/any.hpp>
#include <memory>
#include <unordered_map>
#include <utility>
#include <dao/daoFactory.h>
#include <dao/postgres/factory.h>
namespace Service{
    using namespace DAO;
    template<typename T>
    class Service {
    protected:
        static log4cpp::Category &logger;

    public:
        void setDaoFactory(std::shared_ptr<PostgresDAOFactory> daoFactory) {
            this->daoFactory = daoFactory;
        }

    protected:
        std::shared_ptr<PostgresDAOFactory> daoFactory;
        std::shared_ptr<PooledConnection> connection = nullptr;
        boost::any genericDAO;
        std::string entityClass;

    protected:
        Service(const std::string &entityClass, std::shared_ptr<PostgresDAOFactory> factory) :
                entityClass(entityClass),
                daoFactory(factory) {
            connection = daoFactory->getConnection();
            genericDAO = daoFactory->getDao(entityClass);
        }
    public:
        virtual std::shared_ptr<T> getById(const std::string &id) const = 0;//TODO need to implement base methods

    public:
        virtual std::vector<std::shared_ptr<T>> getAll() const = 0;

    public:
        virtual std::shared_ptr<T> persist(const std::shared_ptr<T> object) const = 0;

    public:
        virtual void remove(const std::shared_ptr<T> object) const = 0;

    public:
        virtual void update(const std::shared_ptr<T> object) const = 0;

    };
    template<typename T>
    log4cpp::Category &Service<T>::logger = log4cpp::Category::getInstance("Service");

    class ServiceCreator {
    public:
        virtual boost::any create(std::shared_ptr<PostgresDAOFactory> daoFactory) const = 0;//TODO need to recode
    };
}

#endif //TASKHIVE_SERVICE_H
