//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_COMMAND_H
#define TASKHIVE_COMMAND_H
#include <controller/controller.h>
#include <controller/Action/action.h>
namespace controller {
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
}


#endif //TASKHIVE_COMMAND_H
