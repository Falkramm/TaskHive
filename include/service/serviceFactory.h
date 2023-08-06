//
// Created by daniil on 7/8/23.
//

#ifndef TASKHIVE_SERVICEFACTORY_H
#define TASKHIVE_SERVICEFACTORY_H

#include <log4cpp/Category.hh>
#include <boost/any.hpp>
#include <memory>
#include <unordered_map>
#include <utility>
#include <service/service.h>
#include <service/userService.h>
#include <service/taskService.h>

namespace Service {
    class ServiceFactory {
    private:
        static log4cpp::Category &logger;
        static std::unordered_map<std::string, std::shared_ptr<ServiceCreator>> creators;
        std::shared_ptr<PostgresDAOFactory> factory;
    public:
        static void init();

    public:
        explicit ServiceFactory(std::shared_ptr<PostgresDAOFactory> factory);

    public:
        ServiceFactory();

    public:
        virtual boost::any getService(const std::string &objectName);

    public:
        void close();

        virtual ~ServiceFactory();
    };
}

#endif //TASKHIVE_SERVICEFACTORY_H
