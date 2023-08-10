//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_LOGOUTACTION_H
#define TASKHIVE_LOGOUTACTION_H
#include <controller/action/authorizedUserAction.h>
namespace controller::Action{
    class LogoutAction: public AuthorizedUserAction<> {
    public:
        LogoutAction(): AuthorizedUserAction(){}

        void exec() override {
            //auto user = getAuthorizedUser();
            //logger.info(String.format("user \"%s\" is logged out", user.getUsername()));
            setAuthorizedUser(nullptr);
        }
    };
}


#endif //TASKHIVE_LOGOUTACTION_H
