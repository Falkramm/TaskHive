//
// Created by daniil on 7/11/23.
//

#ifndef TASKHIVE_ACTION_H
#define TASKHIVE_ACTION_H
#include <service/serviceFactory.h>

namespace controller {
    class Action;

    class Request: public http::request<http::dynamic_body>{
    private:
        std::shared_ptr<Action> action = nullptr;
        std::shared_ptr<User> authorisedUser = nullptr;
    public:
        std::shared_ptr<User> getAuthorisedUser() const {
            return authorisedUser;
        }

        void setAuthorisedUser(std::shared_ptr<User> authorisedUser) {
            Request::authorisedUser = authorisedUser;
        }

        std::shared_ptr<Action> getAction() const {
            return action;
        }

        void setAction(std::shared_ptr<Action> action) {
            Request::action = action;
        }
    };
    class Response: public http::response<http::dynamic_body>{
    private:
        bool completed;
    public:
        Response() : completed(false) {

        }

        bool isCompleted() const {
            return completed;
        }

        void setCompleted(bool completed) {
            Response::completed = completed;
        }

    };
    class Action {
    private:
        std::shared_ptr<std::unordered_set<std::string>> allowRoles;
        std::shared_ptr<User> authorizedUser;
        std::string name;

    protected:
        std::shared_ptr<ServiceFactory> factory;

    public:
        std::shared_ptr<std::unordered_set<std::string> >  getAllowRoles() {
            return allowRoles;
        }

        std::shared_ptr<User> getAuthorizedUser() {
            return authorizedUser;
        }

        void setAuthorizedUser(std::shared_ptr<User> authorizedUser) {
            this->authorizedUser = authorizedUser;
        }

        std::string_view getName() {
            return name;
        }

        void setName(std::string_view name) {
            this->name = name;
        }

        void setFactory(std::shared_ptr<ServiceFactory> factory) {
            this->factory = factory;
        }

        virtual void exec(std::shared_ptr<Request> request, std::shared_ptr<Response> response);


    };

    class ActionCreator {
    public:

        virtual std::shared_ptr<Action> create() const = 0;
    };
}


#endif //TASKHIVE_ACTION_H
