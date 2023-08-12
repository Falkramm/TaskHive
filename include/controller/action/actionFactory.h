//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_ACTIONFACTORY_H
#define TASKHIVE_ACTIONFACTORY_H

#include <controller/action/action.h>
#include <controller/action/authentication/logOutAction.h>
#include <unordered_map>

namespace controller::Action {
    class ActionFactory {
        static std::shared_ptr<std::unordered_map<std::string_view, std::shared_ptr<Action::ActionCreator<void, void>>>> creators;
    public:
        static void init();

        template<typename OutputType, typename ... InputType>
        static std::shared_ptr<Action::GenericAction<OutputType, InputType...>> getAction(std::string_view uri) {
            std::shared_ptr<Action::ActionCreator<OutputType, InputType...>> creator = nullptr;
            if (creators->contains(uri)) {
                creator = creators->find(uri)->second;
            } else {
                throw std::runtime_error("No one any action by that uri");//TODO
            }
            return creator->create();
        }

    };
}


#endif //TASKHIVE_ACTIONFACTORY_H
