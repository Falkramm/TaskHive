//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_AUTHORIZEDUSERACTION_H
#define TASKHIVE_AUTHORIZEDUSERACTION_H
#include <controller/action/action.h>
namespace controller::Action {
    template<class ... Args>
    class AuthorizedUserAction : public GenericAction<Args...> {
    public:
        AuthorizedUserAction() : GenericAction<Args...>() {}
    };
}

#endif //TASKHIVE_AUTHORIZEDUSERACTION_H
