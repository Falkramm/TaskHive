//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_ACTION_H
#define TASKHIVE_ACTION_H


#include <memory>
#include <utility>
#include <entity/User.h>
#include <service/serviceFactory.h>
#include <controller/controller.h>


    namespace controller::Action {
        template<class ... Args>
        class GenericAction {
        private:
            std::shared_ptr<Entity::User> authorizedUser;
            std::string_view name;

        protected:
            std::shared_ptr<Service::ServiceFactory> factory;
        public:

            void setAuthorizedUser(std::shared_ptr<Entity::User> authorizedUser_);

            std::string_view getName();

            void setName(std::string_view name_);

            void setFactory(std::shared_ptr<Service::ServiceFactory> factory_);


            virtual void exec(Args ... ) = 0;
            std::shared_ptr<Entity::User> getAuthorizedUser() const;
        };
        template<class ... Args>
        class ActionCreator{
        public:
            virtual std::shared_ptr<GenericAction<Args...>> create() = 0;
        };
    }

#endif //TASKHIVE_ACTION_H
