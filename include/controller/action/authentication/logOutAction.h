//
// Created by daniil on 8/10/23.
//

#ifndef TASKHIVE_LOGOUTACTION_H
#define TASKHIVE_LOGOUTACTION_H
#include <controller/action/authorizedUserAction.h>
namespace controller::Action{
    class LogoutAction: public GenericAction<bool> {
    public:
        LogoutAction(): GenericAction<bool>(){}

        bool exec() override {
            //auto user = getAuthorizedUser();
            //logger.info(String.format("user \"%s\" is logged out", user.getUsername()));
            setAuthorizedUser(nullptr);
            return getAuthorizedUser() != nullptr;
        }
    };
}


#endif //TASKHIVE_LOGOUTACTION_H
