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
        template<typename OutputType, typename ... InputType>
        class GenericAction {
        private:
            std::shared_ptr<Entity::User> authorizedUser;
            std::string_view name;

        protected:
            std::shared_ptr<Service::ServiceFactory> factory;
        public:
            void setAuthorizedUser(std::shared_ptr<Entity::User> authorizedUser_) {
                this->authorizedUser = std::move(authorizedUser_);
            }

            std::string_view getName() {
                return name;
            }

            void setName(std::string_view name_) {
                this->name = name_;
            }

            void setFactory(std::shared_ptr<Service::ServiceFactory> factory_) {
                this->factory = std::move(factory_);
            }

            std::shared_ptr<Entity::User> getAuthorizedUser() const {
                return authorizedUser;
            }

            virtual OutputType exec(InputType ...) = 0;
        };
        template<typename OutputType, typename ... InputType>
        class ActionCreator{
        public:
            virtual std::shared_ptr<GenericAction<OutputType, InputType ...>> create() = 0;
        };
    }

#endif //TASKHIVE_ACTION_H
