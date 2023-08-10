//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_ACTIONFACTORY_H
#define TASKHIVE_ACTIONFACTORY_H
#include <controller/action/action.h>
#include <unordered_map>
namespace controller::Action {
    class ActionManagerFactory {
        static std::shared_ptr<std::unordered_map<std::string_view , std::shared_ptr<Action::ActionCreator>>> creators;
    public:
        static void init();
        static std::shared_ptr<Action::GenericAction> getAction(std::string_view uri);
    };
}


#endif //TASKHIVE_ACTIONFACTORY_H
