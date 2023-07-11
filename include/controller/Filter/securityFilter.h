//
// Created by daniil on 7/11/23.
//

#ifndef TASKHIVE_SECURITYFILTER_H
#define TASKHIVE_SECURITYFILTER_H
#include <controller/Filter/filter.h>
namespace controller {
    class SecurityFilter: public Filter{
    public:
        void init() override {
            Filter::init();
        }

        void doFilter(std::shared_ptr<Request> request, std::shared_ptr<Response> response,
                      std::shared_ptr<FilterChain> filterChain) const override {
                auto action = request->getAction();
                auto allowRoles = action->getAllowRoles();
                std::string_view userName = "unauthorized user";
//                HttpSession session = httpRequest.getSession();
//                session.setMaxInactiveInterval(10000);
                std::shared_ptr<User> user = request->getAuthorisedUser();
//                logger.debug("AuthorizedUser: " + user);
                bool canExecute = false;
//                canExecute |= (dynamic_cast<std::shared_ptr<LoginAction>>(action) != nullptr) ||
//                        (dynamic_cast<std::shared_ptr<RegistrationAction>>(action) != nullptr);
                if (user != nullptr) {
                    canExecute = true;
                    //canExecute || allowRoles->contains(User.getRole()) != null;
                }
                //logger.debug("CanExecute:" + canExecute);

                if (canExecute) {
                    filterChain->doFilter(request, response);
                } else {
                    //logger.info(String.format("Trying of %s access to forbidden resource \"%s\"", userName, action.getName()));
//                    if (session != null && action.getClass() != MainAction.class) {
//                        session.setAttribute("SecurityFilterMessage", "Доступ запрещён");
//                    }
                }
        }

        ~SecurityFilter() override {

        }
    };
}


#endif //TASKHIVE_SECURITYFILTER_H
