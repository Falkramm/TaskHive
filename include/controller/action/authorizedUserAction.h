//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_AUTHORIZEDUSERACTION_H
#define TASKHIVE_AUTHORIZEDUSERACTION_H

#include <controller/action/action.h>

namespace controller::Action {
    template<typename OutputType, typename ... InputType>
    class AuthorizedUserAction : public GenericAction<OutputType, InputType...> {
    public:
        AuthorizedUserAction() : GenericAction<OutputType, InputType...>() {}
    };
}

#endif //TASKHIVE_AUTHORIZEDUSERACTION_H
